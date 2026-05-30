#include "Scene.hh"
#include <iostream>
using namespace std;
string deleted_items;

void Scene::InitGnuplotLink(PzG::GnuplotLink &rLink) {
  rLink.ZmienTrybRys(PzG::TR_3D);
  rLink.UstawZakresX(-SURFACE_SIZE_X / 2, SURFACE_SIZE_X / 2);
  rLink.UstawZakresY(-SURFACE_SIZE_Y / 2, SURFACE_SIZE_Y / 2);
  rLink.UstawZakresZ(0, 90);
  rLink.UstawRotacjeXZ(40, 60);

  rLink.Inicjalizuj();
}

void Scene::AddToDrawingList(PzG::GnuplotLink &rLink,
                             const GeomObject &rOb) {
  PzG::InfoPlikuDoRysowania *wInfoPliku;

  wInfoPliku = &rLink.DodajNazwePliku(rOb.GetDrawnSolidFilename());
  wInfoPliku->ZmienKolor(rOb.GetColorID());
}

void Scene::RemoveFromDrawingList(PzG::GnuplotLink &rLink,
                                  const GeomObject &rOb) {
  rLink.UsunNazwePliku(rOb.GetDrawnSolidFilename());
}

Scene::Scene() {
  double skala[3] = {20, 20, 10};
  Vector3D Scale(skala);

  double polozenie1[3] = {-100, 0, 0};
  double polozenie2[3] = {0, 100, 0};

  Vector3D Polozenie1(polozenie1);
  Vector3D Polozenie2(polozenie2);

  GeomObjects.push_back(make_shared<RoverSFR>("../model_solids/cube3.dat",
                                              "FSRxpp", Color_LightBlue,
                                              Scale, Polozenie1, 0, 20, 33));
  GeomObjects.push_back(make_shared<RoverSFR>("../model_solids/cube3.dat",
                                           "FSR", Color_LightBlue,
                                           Scale, Polozenie2, 0, 10, 15));

  PlaceSamples();

  for (shared_ptr<GeomObject> &Ob : GeomObjects) {
    AddToDrawingList(Link, *Ob);
    Ob->RecalculateAndSaveVertices();
  }

  InitGnuplotLink(Link);

  if (!InitMarsSurface(Link))
    throw invalid_argument("Invalid Mars surface configuration data");
  
  SelectRover(1);
  Link.Rysuj();
}

shared_ptr<Rover> Scene::SelectRover(unsigned int choice) {
  unsigned int i = 0;

  for (shared_ptr<GeomObject> &Ob : GeomObjects) {
    ++i;

    AddToDrawingList(Link, *Ob);
    Ob->RecalculateAndSaveVertices();

    this->SelectedRover = dynamic_pointer_cast<Rover>(Ob);

    if (i == choice) {
      if (Ob->get_ObjectName().find("FSR", 0) >= 3) {
        this->SelectedRover = dynamic_pointer_cast<RoverSFR>(Ob);
        return dynamic_pointer_cast<RoverSFR>(Ob);
      }
      return dynamic_pointer_cast<Rover>(Ob);
    }
  }
  cout << "Rover number out of range. Selected RoverSFR by default." << endl;
  return nullptr;
}

void Scene::DriveDistance(double distance) {
  list<shared_ptr<GeomObject>> temp_list = GeomObjects;

  double tmp[3] = {distance, 0, 0};
  Vector3D jedz(tmp);
  distance = abs(distance);

  jedz = SelectedRover->rotateZ(jedz, SelectedRover->get_OrientationAngle());
  SelectedRover->set_DistanceToDrive() = distance;
  cout << jedz << endl;

  int t = abs(distance);

  do {
    SelectedRover->set_Position() =
        SelectedRover->get_Position() + jedz / distance;
    SelectedRover->RecalculateAndSaveVertices();
    Link.Rysuj();

    for (shared_ptr<GeomObject> &Ob : temp_list) {
      if (SelectedRover->GetObjectName() != Ob->GetObjectName()) {
        if (Ob->CheckCollision(SelectedRover)) {
          cout << "Collision occurred during drive!" << endl;
          cout << "Press ENTER to allow SFR to shift." << endl;
          t = 1;
        }
      }
    }
    usleep(600000 / SelectedRover->get_Speed());

  } while (--t);
}

void Scene::Rotate(double degrees) {
  if (degrees == 0) return;
  int t = abs(degrees);
  double theta = (degrees * M_PI) / 180;
  double czesc_obrotu = theta / t;

  do {
    SelectedRover->set_OrientationAngle() += czesc_obrotu;
    SelectedRover->RecalculateAndSaveVertices();
    Link.Rysuj();

    for (shared_ptr<GeomObject> &Ob : GeomObjects) {
      if (SelectedRover->GetObjectName() != Ob->GetObjectName()) {
        if (Ob->CheckCollision(SelectedRover)) {
          if (Ob->CheckCollision(SelectedRover) == 1) {
            cout << "Collision occurred during rotation!" << endl;
          }
          cout << "Press ENTER to allow SFR to shift." << endl;
          t = 1;
        }
      }
    }
    usleep(100000 / SelectedRover->get_Speed());

  } while (--t);
}

void Scene::DisplaySampleList() {
  cout << "List of samples on the scene: " << endl;
  int i = 0;

  for (shared_ptr<GeomObject> &Ob : GeomObjects) {
    if (Ob->get_ModelSolidFilename() == "../model_solids/cube2.dat") {
      ++i;
      cout << i << ". " << Ob->get_ObjectName() << endl;
    }
  }
  cout << endl;
}

list<shared_ptr<GeomObject>>::iterator Scene::PickUpSample() {
  double wysoko[3] = {999, 999, 999};
  Vector3D Wysoko(wysoko);

  if (SelectedRover->get_ObjectName().find("FSR", 0) >= 3) {
    cout << "Option only available for RoverSFR!" << endl;
  }
  else {
    auto it = GeomObjects.begin();
 
    for (shared_ptr<GeomObject> &Ob : GeomObjects) {
      if ((*it)->GetObjectName() != "../model_solids/cube3.dat") {
        cout << "Collision Type: " << (*it)->CheckCollision(SelectedRover) << "\n";
        if ((*it)->CheckCollision(SelectedRover)) {
          if ((*it)->CheckCollision(SelectedRover) == DriveOverSample || (*it)->CheckCollision(SelectedRover) == CollisionWithSample) {
            shared_ptr<RoverSFR> roverSFR;
            roverSFR = dynamic_pointer_cast<RoverSFR>(SelectedRover);
            roverSFR->AddSample((*it));
            (*it)->set_Position() = Wysoko;
            (*it)->RecalculateAndSaveVertices();
            deleted_items += ' ' + (*it)->GetObjectName();
            Link.Rysuj();
      
            if ((*it)->GetObjectName() != "../model_solids/cube3.dat") {
              it = GeomObjects.erase(it);
            }
           
            RemoveFromDrawingList(Link, *Ob);
            return it;
          }
        }
      }
      ++it;
    }
  }
  auto it = GeomObjects.begin();
  it++;
  return it;
}

void Scene::PlaceSamples() {
  const char* names[] = {"Alice", "Bob", "Charlie", "David", "Emma", "Frank", "Grace", "Henry", "Ivy", "Jack", "Katie", "Liam", "Mia", "Noah", "Olivia", "Patrick", "Quinn", "Ryan", "Samantha", "Tyler","Alice1", "Bob1", "Charlie1", "David1", "Emma1", "Frank1", "Grace1", "Henry1", "Ivy1", "Jack1", "Katie1", "Liam1", "Mia1", "Noah1", "Olivia1", "Patrick1", "Quinn1", "Ryan1", "Samantha1", "Tyler1"};
  AdjacencyListGraph<std::pair<int,int>> l;

  for (int i = 0; i < 15; i++) {
    double skala[3] = {20, 20, 10};
    Vector3D Scale(skala);

    double x = rand() % 200;
    double y = rand() % 200;
    double polozenie[3] = {x - 100, y - 100, 0};
    Vector3D Position(polozenie);
    l.insertEdge(l.insertVertex({x, y}), l.insertVertex({0, 0}), 10);
      
    GeomObjects.push_back(
        make_shared<RegolithSample>("../model_solids/cube2.dat", names[i],
                                    Color_Red, Scale * 0.2, Position, 0));
  }

  l.print();
}

void Scene::AutonomousDrive() {
  float delta_x, delta_y;
  cout << "Autonomous drive initialized.\n";

  while (1) {
    list<shared_ptr<GeomObject>>::iterator it = GeomObjects.begin();
    int shortest_distance = INT_MAX;
    int sample_count = 0;

    for (list<shared_ptr<GeomObject>>::iterator kt = GeomObjects.begin(); kt != GeomObjects.end(); ++kt) {
      if ((*kt)->get_ModelSolidFilename() != "../model_solids/cube3.dat") {
        sample_count++;
        delta_x = -SelectedRover->get_Position().return_x() + (*kt)->get_Position().return_x();
        delta_y = -SelectedRover->get_Position().return_y() + (*kt)->get_Position().return_y();
      
        if (shortest_distance > sqrt(delta_x * delta_x + delta_y * delta_y)) {
          shortest_distance = sqrt(delta_x * delta_x + delta_y * delta_y);
          it = kt;
        }
        list<shared_ptr<GeomObject>>::iterator end = kt;
        end++;
        if (end == GeomObjects.end() && (shortest_distance == INT_MAX)) {
          return;
        }
      }
    }

    if (!sample_count) return;

    delta_x = -SelectedRover->get_Position().return_x() + (*it)->get_Position().return_x();
    delta_y = -SelectedRover->get_Position().return_y() + (*it)->get_Position().return_y();

    float tan = (atan2(delta_y, delta_x)) * (180 / 3.14);

    Rotate(tan - (SelectedRover->get_OrientationAngle() * (180 / 3.14)));
    DriveDistance(sqrt(delta_x * delta_x + delta_y * delta_y));
    it = PickUpSample();
    cout << "Tangens: " << tan << "\n";
    cout << "Orientation: " << -SelectedRover->get_OrientationAngle() << "\n";
  }

  cout << "Autonomous drive complete.\n";
}

void Scene::Menu() {
  int t = 1, wybor;
  char znak;
  double odleglosc, kat;

  while (t) {
    cout << "--------------------------------------" << endl;
    cout << "a - autonomous drive \nj - drive straight \no - change orientation \np - pick up sample (RoverSFR only)\nw - select rover \nl - list samples on scene \nm - display menu\n\nk - exit program \n--------------------------------------\nYour choice: ";

    cin >> znak;
    switch (znak) {
    case 'a':
      cout << "Autonomous driving" << endl;
      AutonomousDrive();
      break;
    case 'j':
      cout << "Enter distance to drive: " << endl;
      cin >> odleglosc;
      DriveDistance(odleglosc);
      break;
    case 'o':
      cout << "Enter angle to rotate: " << endl;
      cin >> kat;
      Rotate(kat);
      break;
    case 'p':
      PickUpSample();
      cout << endl;
      break;
    case 'w':
      cout << "Enter rover index to select: " << endl;
      cin >> wybor;
      SelectRover(wybor);
      break;
    case 'l':
      DisplaySampleList();
      break;
    case 'm':
      t = 0;
      break;
    case 'k':
      t = 0;
      break;
    default:
      cout << "Please select a valid option." << endl;
      break;
    }
  }

  cout << deleted_items << " Deleted items\n";
}
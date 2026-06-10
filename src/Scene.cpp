#include "Scene.hh"
#include <iostream>
#include <limits>
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
  Vector3D Scale{20, 20, 10};
  Vector3D Position1{-100, 0, 0};
  Vector3D Position2{0, 100, 0};

  GeomObjects.push_back(make_shared<RoverSFR>("../model_solids/cube3.dat",
                                              "FSRxpp", static_cast<int>(Colors::LightBlue),
                                              Scale, Position1, 0, 20, 33));
  GeomObjects.push_back(make_shared<RoverSFR>("../model_solids/cube3.dat",
                                           "FSR", static_cast<int>(Colors::LightBlue),
                                           Scale, Position2, 0, 10, 15));

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

    if (i == choice) {
      if (auto rover = dynamic_pointer_cast<Rover>(Ob)) {
        this->SelectedRover = rover;
        return rover;
      }
    }
  }
  cout << "Rover number out of range. Defaulting to nullptr." << endl;
  return nullptr;
}

void Scene::DriveDistance(double distance) {
  list<shared_ptr<GeomObject>> tempList = GeomObjects;

  Vector3D driveVector{distance, 0, 0};
  distance = abs(distance);

  driveVector = SelectedRover->rotateZ(driveVector, SelectedRover->get_OrientationAngle());
  SelectedRover->set_DistanceToDrive(distance);
  cout << driveVector << endl;

  int t = abs(distance);

  do {
    SelectedRover->set_Position(SelectedRover->get_Position() + driveVector / distance);
    SelectedRover->RecalculateAndSaveVertices();
    Link.Rysuj();

    for (shared_ptr<GeomObject> &Ob : tempList) {
      if (SelectedRover->GetObjectName() != Ob->GetObjectName()) {
        if (Ob->CheckCollision(SelectedRover) != CollisionType::NoCollision) {
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
    SelectedRover->set_OrientationAngle(SelectedRover->get_OrientationAngle() + czesc_obrotu);
    SelectedRover->RecalculateAndSaveVertices();
    Link.Rysuj();

    for (shared_ptr<GeomObject> &Ob : GeomObjects) {
      if (SelectedRover->GetObjectName() != Ob->GetObjectName()) {
        CollisionType col = Ob->CheckCollision(SelectedRover);
        if (col != CollisionType::NoCollision) {
          if (col == CollisionType::DriveOverSample) {
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
  Vector3D highAltitude{999, 999, 999};

  if (!SelectedRover || !SelectedRover->CanPickSamples()) {
    cout << "Option only available for RoverSFR!" << endl;
  }
  else {
    auto it = GeomObjects.begin();
    while (it != GeomObjects.end()) {
      shared_ptr<GeomObject> ob = *it;
      if (ob->GetObjectName() != "../model_solids/cube3.dat") {
        CollisionType colType = ob->CheckCollision(SelectedRover);
        cout << "Collision Type: " << colType << "\n";
        if (colType == CollisionType::DriveOverSample || colType == CollisionType::CollisionWithSample) {
          SelectedRover->AddSample(ob);
          ob->set_Position(highAltitude);
          ob->RecalculateAndSaveVertices();
          deleted_items += ' ' + ob->GetObjectName();
          Link.Rysuj();
          
          RemoveFromDrawingList(Link, *ob);
          
          it = GeomObjects.erase(it);
          return it;
        }
      }
      ++it;
    }
  }
  auto it = GeomObjects.begin();
  if (it != GeomObjects.end()) {
    it++;
  }
  return it;
}

void Scene::PlaceSamples() {
  const char* names[] = {"Alice", "Bob", "Charlie", "David", "Emma", "Frank", "Grace", "Henry", "Ivy", "Jack", "Katie", "Liam", "Mia", "Noah", "Olivia", "Patrick", "Quinn", "Ryan", "Samantha", "Tyler","Alice1", "Bob1", "Charlie1", "David1", "Emma1", "Frank1", "Grace1", "Henry1", "Ivy1", "Jack1", "Katie1", "Liam1", "Mia1", "Noah1", "Olivia1", "Patrick1", "Quinn1", "Ryan1", "Samantha1", "Tyler1"};
  AdjacencyListGraph<std::pair<int,int>> l;

  for (int i = 0; i < 15; i++) {
    Vector3D scale{20, 20, 10};

    double x = rand() % 200;
    double y = rand() % 200;
    Vector3D position{x - 100, y - 100, 0};
    l.insertEdge(l.insertVertex({x, y}), l.insertVertex({0, 0}), 10);
      
    GeomObjects.push_back(
        make_shared<RegolithSample>("../model_solids/cube2.dat", names[i],
                                    static_cast<int>(Colors::Red), scale * 0.2, position, 0));
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

template <typename T>
static T PromptInput(const string& prompt) {
  T value;
  while (true) {
    cout << prompt;
    if (cin >> value) {
      return value;
    }
    cout << "Invalid input! Please try again.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

static void PrintMenu() {
  cout << R"(--------------------------------------
a - autonomous drive 
j - drive straight 
o - change orientation 
p - pick up sample (RoverSFR only)
w - select rover 
l - list samples on scene 
m - display menu

k - exit program 
--------------------------------------)" << endl;
}

void Scene::Menu() {
  PrintMenu();

  while (true) {
    char choice = PromptInput<char>("Your choice (m for menu): ");

    switch (choice) {
      case 'a': {
        cout << "Autonomous driving" << endl;
        AutonomousDrive();
        break;
      }
      case 'j': {
        DriveDistance(PromptInput<double>("Enter distance to drive: "));
        break;
      }
      case 'o': {
        Rotate(PromptInput<double>("Enter angle to rotate: "));
        break;
      }
      case 'p': {
        PickUpSample();
        cout << endl;
        break;
      }
      case 'w': {
        SelectRover(PromptInput<unsigned int>("Enter rover index to select: "));
        break;
      }
      case 'l': {
        DisplaySampleList();
        break;
      }
      case 'm': {
        PrintMenu();
        break;
      }
      case 'k': {
        cout << deleted_items << " Deleted items\n";
        return;
      }
      default: {
        cout << "Please select a valid option." << endl;
        break;
      }
    }
    cout << endl;
  }
}
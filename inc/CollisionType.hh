#pragma once

enum class CollisionType : uint8_t {
    NoCollision,
    DriveOverSample,
    Collision,
    CollisionWithSample // no possibility to drive over the sample
};

inline std::ostream& operator<<(std::ostream& os, CollisionType type) {
    switch (type) {
        case CollisionType::NoCollision:
            return os << "No Collision";
        case CollisionType::DriveOverSample:
            return os << "Drive Over Sample";
        case CollisionType::Collision:
            return os << "Collision";
        case CollisionType::CollisionWithSample:
            return os << "Collision With Sample";
        default:
            return os << "Unknown";
    }
}

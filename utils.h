enum enum_object_types {
    obj_grass_1,
    obj_grass_2,
    obj_coin
};

typedef struct Object {
    int object_type;
    int x;
    int y;
    double percent;
} Object;

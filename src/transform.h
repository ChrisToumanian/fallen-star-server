#ifndef TRANSFORM_H
#define TRANSFORM_H

struct Position
{
	float x = 0;
	float y = 0;
	float z = 0;
};

class Transform
{
public:
	Transform();

    Position position;
    float rotation = 180;
    float scale = 1;
};

#endif
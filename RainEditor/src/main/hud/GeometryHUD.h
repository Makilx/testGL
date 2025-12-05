#pragma once
#include <main/Geometry.h>
#include <imgui/imgui.h>   

class GeometryHUD {
public:
	GeometryHUD(Geometry *geometry);

	void Draw();

private:
	Geometry* currentGeometry;
};
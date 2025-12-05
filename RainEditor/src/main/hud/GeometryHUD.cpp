#include "GeometryHUD.h"

GeometryHUD::GeometryHUD(Geometry *geo) : currentGeometry(geo) {

}

void GeometryHUD::Draw() {
	// Draw tile picker menu
	ImGui::Begin("Geometry");
	
	// Title
	ImGui::Text("Picker");

	// Options
	ImGui::Button("Picker");

	ImGui::End();
}
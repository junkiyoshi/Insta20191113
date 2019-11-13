#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	auto radius = 125;
	for (auto x = -300; x <= 300; x += 300) {

		for (auto y = -300; y <= 300; y += 300) {

			auto location = glm::vec3(x, y, 0);
			for (auto deg = 0; deg < 360; deg += 1) {

				int index = this->mesh.getVertices().size();
				vector<glm::vec3> vertices = {
					glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 3),
					glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), 3),
					glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), -3),
					glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), -3)
				};

				for (auto& vertex : vertices) {

					auto noise_seed_x = location.x + vertex.x * 0.003;
					auto noise_seed_y = location.y + vertex.y * 0.003;
					auto noise_seed_z = location.z + vertex.z * 0.003;

					auto angle_x = ofMap(ofNoise(noise_seed_x, ofGetFrameNum() * 0.001), 0, 1, -PI * 2, PI * 2);
					auto angle_y = ofMap(ofNoise(noise_seed_y, ofGetFrameNum() * 0.001), 0, 1, -PI * 2, PI * 2);
					auto angle_z = ofMap(ofNoise(noise_seed_z, ofGetFrameNum() * 0.001), 0, 1, -PI * 2, PI * 2);

					auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
					auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
					auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

					this->mesh.addVertex(location + glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_x);
				}

				this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 1); this->mesh.addIndex(index + 2);
				this->mesh.addIndex(index + 0); this->mesh.addIndex(index + 3); this->mesh.addIndex(index + 2);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	this->mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
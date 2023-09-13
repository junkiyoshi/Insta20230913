#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableDepthTest();

	for (auto v = 0; v < 360; v += 2) {

		for (auto u = 0; u < 360; u += 5) {

			this->location_list.push_back(this->make_point(200, 80, u, v));
			this->height_list.push_back(0);
		}
	}

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face_mesh.clear();
	this->frame_mesh.clear();

	auto R = 200;
	auto r = 80;
	auto v_span = 2;
	auto u_span = 5;

	for (int i = 0; i < this->height_list.size(); i++) {

		auto noise_value = ofNoise(glm::vec4(this->location_list[i] * 0.01, ofGetFrameNum() * 0.01));
		if (noise_value > 0.8) {
		
			this->height_list[i] > -65 ? this->height_list[i] -= ofMap(noise_value, 0.8, 1, 5, 15) : this->height_list[i] = -65;
		}
		else {

			this->height_list[i] < 0 ? this->height_list[i] += 3 : this->height_list[i] = 0;
		}
	}

	int index = 0;
	for (auto v = 0; v < 360; v += v_span) {

		for (auto u = 0; u < 360; u += u_span) {

			auto height = this->height_list[index++];

			vector<glm::vec3> vertices;
			vertices.push_back(this->make_point(R, r, u, v));
			vertices.push_back(this->make_point(R, r, u + u_span, v));
			vertices.push_back(this->make_point(R, r, u + u_span, v + v_span));
			vertices.push_back(this->make_point(R, r, u, v + v_span));
			vertices.push_back(this->make_point(R, r + height, u, v));
			vertices.push_back(this->make_point(R, r + height, u + u_span, v));
			vertices.push_back(this->make_point(R, r + height, u + u_span, v + v_span));
			vertices.push_back(this->make_point(R, r + height, u, v + v_span));

			vector<glm::vec3> vertices_2;
			vertices_2.push_back(this->make_point(R, r, u, v, 0.999));
			vertices_2.push_back(this->make_point(R, r, u + u_span, v, 0.999));
			vertices_2.push_back(this->make_point(R, r, u + u_span, v + v_span, 0.999));
			vertices_2.push_back(this->make_point(R, r, u, v + v_span, 0.999));
			vertices_2.push_back(this->make_point(R, r + height, u, v, 0.999));
			vertices_2.push_back(this->make_point(R, r + height, u + u_span, v, 0.999));
			vertices_2.push_back(this->make_point(R, r + height, u + u_span, v + v_span, 0.999));
			vertices_2.push_back(this->make_point(R, r + height, u, v + v_span, 0.999));

			int index = this->face_mesh.getNumVertices();
			this->face_mesh.addVertices(vertices);
			this->frame_mesh.addVertices(vertices_2);

			// Face Index

			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 2);
			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 3);

			this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);
			this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 7);

			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 5);
			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 1);

			this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);
			this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 2);

			this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 7);
			this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 7); this->face_mesh.addIndex(index + 3);

			this->face_mesh.addIndex(index + 3); this->face_mesh.addIndex(index + 7); this->face_mesh.addIndex(index + 4);
			this->face_mesh.addIndex(index + 3); this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 0);

			// Frame Index

			this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 1);
			this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 2);
			this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 3);
			this->frame_mesh.addIndex(index + 3); this->frame_mesh.addIndex(index + 0);

			this->frame_mesh.addIndex(index + 4); this->frame_mesh.addIndex(index + 5);
			this->frame_mesh.addIndex(index + 5); this->frame_mesh.addIndex(index + 6);
			this->frame_mesh.addIndex(index + 6); this->frame_mesh.addIndex(index + 7);
			this->frame_mesh.addIndex(index + 7); this->frame_mesh.addIndex(index + 4);

			this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 4);
			this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 5);
			this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 6);
			this->frame_mesh.addIndex(index + 3); this->frame_mesh.addIndex(index + 7);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	int R = 200;
	int r = 60;

	this->cam.begin();
	ofRotateX(90);
	this->cam.setPosition(R, 0, r * 2);
	ofRotateZ(ofGetFrameNum());

	ofSetColor(0);
	this->face_mesh.drawFaces();

	ofSetColor(255);
	this->frame_mesh.drawWireframe();


	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v, float scale) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u) * scale) * cos(v);
	auto y = (R + r * cos(u) * scale) * sin(v);
	auto z = r * sin(u) * scale;

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
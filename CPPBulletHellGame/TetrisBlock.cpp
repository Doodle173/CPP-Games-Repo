#include "TetrisBlock.h"

#include<fstream>
#include<sstream>

void TetrisBlock::Load(const GLchar *file, GLuint blockWidth, GLuint blockHeight) {
	this->Block.clear();

	GLuint blockCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> blockData;

	if (fstream) {
		while(std::getline(fstream, line)){
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while(sstream >> blockCode){
				row.push_back(blockCode);
			}
			if(blockData.size() > 0){
				this->init(blockData, blockWidth, blockHeight);
			}
		}
	}
}

void TetrisBlock::Draw(SpriteRenderer &renderer) {
	for (GameObject& block : this->Block)
		if (!block.Destroyed)
			block.Draw(renderer);
}

void TetrisBlock::init(std::vector < std::vector<GLuint>> blockData, GLuint blockWidth, GLuint blockHeight) {
	//Calculate Dimensions
	GLuint height = blockData.size();
	GLuint width = blockData[0].size(); // index vector p9[ since function is only called if height > 0
	GLfloat unit_width = blockWidth / static_cast<GLfloat>(width), unit_height = blockHeight/ height;

	//initialize blocks from blockData
	for (GLuint y = 0; y < height; ++ y) {
		for (GLuint x = 0; x < width; ++x) {
			//check block type from level data
			if (blockData[y][x] == 1) { //solid
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);

				GameObject obj(pos, size, ResourceManager::GetTexture("block_blue"), glm::vec3(0.8f, 0.8f, 0.8f));

				obj.IsSolid = GL_TRUE;
				this->Block.push_back(obj);
			}
			else if(blockData[y][x] == 1) {
				glm::vec3 color = glm::vec3(1.0f); // set color to white
				if (blockData[y][x] == 2) {
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				}
				else if (blockData[y][x] == 3) {
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				}
				else if (blockData[y][x] == 4) {
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				}
				else if (blockData[y][x] == 5) {
					color = glm::vec3(1.0f, 0.5f, 0.0f);
					
					glm::vec2 pos(unit_width * x, unit_height * y);
					glm::vec2 size(unit_width, unit_height);
					this->Block.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
				}
			}
			
		}
	}
}
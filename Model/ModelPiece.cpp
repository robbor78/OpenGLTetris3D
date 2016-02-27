#include "ModelPiece.h"

namespace Tetris3D {

ModelPiece::ModelPiece(OpenGLProgram* program) :
		AbstractModelPiece(program) {
	logger->info("Initialising model piece.");

	piece = 0;
	vbo = -1;
	ibo = -1;
	isWireFrame = false;

	logger->info("Initialised model piece.");
}

ModelPiece::~ModelPiece() {
	logger->info("Stopping model piece.");
	piece = 0;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	logger->info("Stopped model piece.");
}

void ModelPiece::GenerateBuffers() {
	std::vector<float> cs;
	std::vector<unsigned short> el;
	Convert(cs, el);

	GenerateArrayBuffer(vbo, cs);
	GenerateElementBuffer(ibo, el);
}

void ModelPiece::InitBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	AbstractModelPiece::InitBuffers();
}


void ModelPiece::DrawBuffers() {
	int size = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelPiece::Convert(std::vector<float> &cs, std::vector<unsigned short> &el) {
	cs.clear();
	el.clear();

	unsigned int col = piece->GetCol();
	unsigned int row = piece->GetRow();
	unsigned int dep = piece->GetDep();

	int numElements = 24;
	int cubeNum = 0;

	for (unsigned int c = 0; c < col; c++) {

		for (unsigned int r = 0; r < row; r++) {
			for (unsigned int d = 0; d < dep; d++) {
				Voxel* v = (*piece)(c, r, d);
				if (v == 0)
					continue;

				int col = v->GetLocation().col + piece->GetLocation().col;
				int row = v->GetLocation().row + piece->GetLocation().row;
				int dep = v->GetLocation().dep + piece->GetLocation().dep;

				float f_bl[3] = { (float) (col * sideLength +xOffset), (float) (-(row + 1) * sideLength + yOffset), (float) (dep
						* sideLength) };
				float f_br[3] = { f_bl[0] + sideLength, f_bl[1], f_bl[2] };
				float f_tl[3] = { f_bl[0], f_bl[1] + sideLength, f_bl[2] };
				float f_tr[3] = { f_br[0], f_tl[1], f_bl[2] };
				float b_tl[3] = { f_tl[0], f_tl[1], f_bl[2] + sideLength };
				float b_tr[3] = { f_tr[0], f_tr[1], b_tl[2] };
				float b_bl[3] = { f_bl[0], f_bl[1], b_tl[2] };
				float b_br[3] = { f_tr[0], f_bl[1], b_tl[2] };

				//front
				VoxelColour colour = v->GetColour();
				PushIntoVector(cs, f_bl, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { colour.red, colour.blue, colour.green,
						colour.alpha });
				PushIntoVector(cs, f_br, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { colour.red, colour.blue, colour.green,
						colour.alpha });
				PushIntoVector(cs, f_tr, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { colour.red, colour.blue, colour.green,
						colour.alpha });
				PushIntoVector(cs, f_tl, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { colour.red, colour.blue, colour.green,
						colour.alpha });

				//top
				PushIntoVector(cs, f_tl, new float[3] { 0.0, 1.0, 0.0 }, new float[4] { 0.0, 0.5, 0.0, 1.0 });
				PushIntoVector(cs, f_tr, new float[3] { 0.0, 1.0, 0.0 }, new float[4] { 0.0, 0.5, 0.0, 1.0 });
				PushIntoVector(cs, b_tr, new float[3] { 0.0, 1.0, 0.0 }, new float[4] { 0.0, 0.5, 0.0, 1.0 });
				PushIntoVector(cs, b_tl, new float[3] { 0.0, 1.0, 0.0 }, new float[4] { 0.0, 0.5, 0.0, 1.0 });

				//back
				PushIntoVector(cs, b_br, new float[3] { 0.0, 0.0, 1.0 }, new float[4] { 1.0f - colour.red, 1.0f - colour.blue,
						1.0f - colour.green, colour.alpha });
				PushIntoVector(cs, b_bl, new float[3] { 0.0, 0.0, 1.0 }, new float[4] { 1.0f - colour.red, 1.0f - colour.blue,
						1.0f - colour.green, colour.alpha });
				PushIntoVector(cs, b_tl, new float[3] { 0.0, 0.0, 1.0 }, new float[4] { 1.0f - colour.red, 1.0f - colour.blue,
						1.0f - colour.green, colour.alpha });
				PushIntoVector(cs, b_tr, new float[3] { 0.0, 0.0, 1.0 }, new float[4] { 1.0f - colour.red, 1.0f - colour.blue,
						1.0f - colour.green, colour.alpha });

				//bottom
				PushIntoVector(cs, b_bl, new float[3] { 0.0, -1.0, 0.0 }, new float[4] { 0.5, 0.0, 0.0, 1.0 });
				PushIntoVector(cs, b_br, new float[3] { 0.0, -1.0, 0.0 }, new float[4] { 0.5, 0.0, 0.0, 1.0 });
				PushIntoVector(cs, f_br, new float[3] { 0.0, -1.0, 0.0 }, new float[4] { 0.5, 0.0, 0.0, 1.0 });
				PushIntoVector(cs, f_bl, new float[3] { 0.0, -1.0, 0.0 }, new float[4] { 0.5, 0.0, 0.0, 1.0 });

				//left
				PushIntoVector(cs, b_bl, new float[3] { -1.0, 0.0, 0.0 }, new float[4] { 0.0, 0.0, 5.0, 1.0 });
				PushIntoVector(cs, f_bl, new float[3] { -1.0, 0.0, 0.0 }, new float[4] { 0.0, 0.0, 5.0, 1.0 });
				PushIntoVector(cs, f_tl, new float[3] { -1.0, 0.0, 0.0 }, new float[4] { 0.0, 0.0, 5.0, 1.0 });
				PushIntoVector(cs, b_tl, new float[3] { -1.0, 0.0, 0.0 }, new float[4] { 0.0, 0.0, 5.0, 1.0 });

				//right
				PushIntoVector(cs, f_br, new float[3] { 1.0, 0.0, 0.0 }, new float[4] { 0.5, 0.2, 0.0, 1.0 });
				PushIntoVector(cs, b_br, new float[3] { 1.0, 0.0, 0.0 }, new float[4] { 0.5, 0.2, 0.0, 1.0 });
				PushIntoVector(cs, b_tr, new float[3] { 1.0, 0.0, 0.0 }, new float[4] { 0.5, 0.2, 0.0, 1.0 });
				PushIntoVector(cs, f_tr, new float[3] { 1.0, 0.0, 0.0 }, new float[4] { 0.5, 0.2, 0.0, 1.0 });

				MakeElements(el, numElements, cubeNum);

				cubeNum++; //increment the cube counter;

			}

		}
	}

}

void ModelPiece::MakeElements(std::vector<unsigned short> &el, int numElements, int cubeNum) {

	int offset = numElements * cubeNum;
//front
	el.push_back(0 + offset);
	el.push_back(1 + offset);
	el.push_back(2 + offset);
	el.push_back(2 + offset);
	el.push_back(3 + offset);
	el.push_back(0 + offset);
//top
	el.push_back(4 + offset);
	el.push_back(5 + offset);
	el.push_back(6 + offset);
	el.push_back(6 + offset);
	el.push_back(7 + offset);
	el.push_back(4 + offset);
//back
	el.push_back(8 + offset);
	el.push_back(9 + offset);
	el.push_back(10 + offset);
	el.push_back(10 + offset);
	el.push_back(11 + offset);
	el.push_back(8 + offset);
//bottom
	el.push_back(12 + offset);
	el.push_back(13 + offset);
	el.push_back(14 + offset);
	el.push_back(14 + offset);
	el.push_back(15 + offset);
	el.push_back(12 + offset);
//left
	el.push_back(16 + offset);
	el.push_back(17 + offset);
	el.push_back(18 + offset);
	el.push_back(18 + offset);
	el.push_back(19 + offset);
	el.push_back(16 + offset);
//rightunsigned
	el.push_back(20 + offset);
	el.push_back(21 + offset);
	el.push_back(22 + offset);
	el.push_back(22 + offset);
	el.push_back(23 + offset);
	el.push_back(20 + offset);

}

} /* namespace Tetris3D */

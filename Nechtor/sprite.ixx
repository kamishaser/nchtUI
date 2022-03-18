export module sprite;
import GUIelement;
import <array>;
import <memory>;
import <functional>;
import <iostream>;
import <iomanip>;
import <vector>;
import <SFML/Graphics.hpp>;
import <algorithm>;



//Shader* texShader;

unsigned int VBO;
unsigned int EBO;
unsigned int VAO;


//export class sprite : public GUIelement
//{
//	
//	
//public:
//	unsigned int ID;
//	static void activate(Shader* shader)
//	{
//		texShader = shader;
//		glGenBuffers(1, &VBO);
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(1, &EBO);
//		
//		std::vector<Shader::vertexAtrib> vatrib;
//		vatrib.emplace_back(0, GL_FLOAT, 3);
//		vatrib.emplace_back(1, GL_FLOAT, 2);
//		shader->setVertexAtrib(vatrib);
//	}
//	void draw()
//	{
//
//		std::array<sf::Vector2f, 4> verticles = getVerticles();//cruch
//		float tver[] //cruch
//		{
//			0, 1,
//			1, 1,
//			0, 0,
//			1, 0,
//			
//
//		};
//		float out[20];
//		
//		for (int i = 0; i < 4; i++)
//		{
//			out[i * 5] = verticles[i].x;
//			out[i * 5 + 1] = verticles[i].y;
//			out[i * 5 + 2] = 0.0f;
//			out[i * 5 + 3] = tver[i * 2];
//			out[i * 5 + 4] = tver[i * 2 + 1];
//		}
//		unsigned int indices[]
//		{  // cruch
//			0, 1, 2, // первый треугольник
//			1, 3, 2  // второй треугольник
//		};
//		
//		
//
//		glBindVertexArray(VAO);//связывание объекта вершинного массива
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(out), out, GL_STREAM_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
//
//		glActiveTexture(GL_TEXTURE0);
//		TexturePack::use(ID);
//		texShader->use();
//		std::cout << "draw" << std::endl;
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//	}
//
//	sprite(std::weak_ptr<GUIelement> tc, int pfix, int tfix, sf::Vector2f ot, sf::Vector2f sz, unsigned int textureID)
//		:GUIelement(tc, pfix, tfix, ot, sz), ID(textureID)
//	{}
//
//	void setTexture(unsigned int newID)
//	{
//		ID = newID;
//	}
//
//};
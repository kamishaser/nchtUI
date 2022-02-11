export module rectangleShape;
import GUIelement;


export class rectangle : public GUIelement::shape
{
public:
	virtual void draw(glm::vec2 parPointPos);
	virtual glm::vec2 getPoint(int number);

};
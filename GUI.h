#ifndef GUI_H
#define GUI_H

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	const float p2pX(const float perc, const sf::VideoMode& vm);
	const float p2pY(const float perc, const sf::VideoMode& vm);
	const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);

	class Buttons
	{
	protected:
		short unsigned buttonState;
		short unsigned id;

		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;
		bool press;


	public:

		virtual ~Buttons();
		//Accessors
		bool isPressed();
		bool wasPressed();
		void setPressAfterSuccessfullTransaction();
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Functions
		virtual void update(const sf::Vector2i& mousePosWindow) = 0;
		virtual void render(sf::RenderTarget* target) = 0;
	};
	class ButtonMenu
		:public Buttons
	{
	private:

		sf::RectangleShape shape;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		ButtonMenu(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		virtual ~ButtonMenu();

		//Accessors

		//Modifiers

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget* target);
	};
	class ButtonBuildingMenu
		:public Buttons
	{
	private:
		int cost;
		sf::IntRect bounds;
		sf::Sprite BMENU_button;
		sf::Texture BMENU_texture;

	public:
		ButtonBuildingMenu(float x, float y,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, std::string which,
			short unsigned id = 0);
		void GetTextureRect(std::string a);
		void SetTextureRect();
		void initButtonTexture();
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget* target);
		float getXbounds();
		float getYbounds();
		int getCost();
	};

	class PlayerGui	
{
protected:
	sf::Text text;
	sf::Sprite texture;
	sf::Texture loadTexture;
	std::string Hp_text;
	int max_value;
public:
	virtual void update(const int current_value) = 0;
	void render(sf::RenderTarget *target);
	virtual void initTexture() = 0;

};
class HP_BAR :
	public PlayerGui
{
private:

public:
	void update(const int current_value);
	HP_BAR(int max_value, sf::Font &font, sf::VideoMode &vm);
	void initTexture();
};


class CoinIndicator:
	public PlayerGui
{
public:
	CoinIndicator(int StartingValue, sf::Font &font, sf::VideoMode &vm);
	void update(const int current_value);
	void initTexture();
};
}
#endif

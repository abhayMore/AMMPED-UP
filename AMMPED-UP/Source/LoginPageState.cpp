#include "../Header Files/LoginPageState.h"
#include "../Header Files/MainMenu.h"

LoginPageState::LoginPageState(std::shared_ptr<Context>& context) :
	m_context(context)
{
    file = std::ifstream("key.json");
    jsonFile = nlohmann::json::parse(file);
}

LoginPageState::~LoginPageState()
{
}

void LoginPageState::init()
{
    m_context->m_assets->addFont(LOGIN_FONT, "Resources/fonts/Arial.ttf");

    //BACKGROUND 
    m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/login.png");
    m_loginBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
    m_loginBackground.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
    m_loginBackground.setOrigin(sf::Vector2f(m_loginBackground.getTexture()->getSize().x / 2, m_loginBackground.getTexture()->getSize().y / 2));
    m_loginBackground.setScale({ 2,2 });

	//SIGN IN TITLE
    m_signInTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
    m_signInTitle.setString("SIGN IN");
    m_signInTitle.setCharacterSize(35);
    m_signInTitle.setOrigin(m_signInTitle.getLocalBounds().width / 2, m_signInTitle.getLocalBounds().height / 2);
    m_signInTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 175.0f);

	//USERNAME TITLE
	m_userNameTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_userNameTitle.setString("Username");
	m_userNameTitle.setCharacterSize(25);
	m_userNameTitle.setOrigin(m_userNameTitle.getLocalBounds().width / 2, m_userNameTitle.getLocalBounds().height / 2);
	m_userNameTitle.setPosition(m_context->m_window->getSize().x / 4 + 2, m_context->m_window->getSize().y / 2 - 80.0f);

	//USERNAME TEXTBOX
    m_allTextBoxes[0] = Textbox({ 400,25 },20, sf::Color::Black, sf::Color::Transparent,sf::Color::White, true);
    m_allTextBoxes[0].setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_allTextBoxes[0].setPosition(sf::Vector2f( m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 - 50.0f ));

	//EMAIL TITLE
	m_emailIDTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_emailIDTitle.setString("Email");
	m_emailIDTitle.setCharacterSize(25);
	m_emailIDTitle.setOrigin(m_emailIDTitle.getLocalBounds().width / 2, m_emailIDTitle.getLocalBounds().height / 2);
	m_emailIDTitle.setPosition(m_context->m_window->getSize().x / 4 - m_emailIDTitle.getGlobalBounds().width / 2 + 7, m_context->m_window->getSize().y / 2 );

	//EMAIL TEXTBOX
    m_allTextBoxes[1] = Textbox({ 400,25 }, 20, sf::Color::Black, sf::Color::Transparent, sf::Color::White, false);
    m_allTextBoxes[1].setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_allTextBoxes[1].setPosition(sf::Vector2f(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 + 30.0f));

	//PASSWORD TITTLE
	m_passwordTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_passwordTitle.setString("Password");
	m_passwordTitle.setCharacterSize(25);
	m_passwordTitle.setOrigin(m_passwordTitle.getLocalBounds().width / 2, m_passwordTitle.getLocalBounds().height / 2);
	m_passwordTitle.setPosition(m_context->m_window->getSize().x / 4, m_context->m_window->getSize().y / 2 + 80.0f);

	//PASSWORD TEXTBOX
    m_allTextBoxes[2] = Textbox({ 400,25 }, 20, sf::Color::Black, sf::Color::Transparent, sf::Color::White, false);
    m_allTextBoxes[2].setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_allTextBoxes[2].setPosition(sf::Vector2f(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 + 110.0f));

	//SIGN IN BUTTON
	m_signInButton = Button("Sign In",{ 150,50 }, 35, sf::Color::Green, sf::Color::White);
	m_signInButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_signInButton.setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2 - m_signInButton.getButtonSize().x / 2, m_context->m_window->getSize().y - 50.0f - m_signInButton.getButtonSize().y / 2));
}

void LoginPageState::processInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            m_context->m_window->close();
            break;
        }
        case sf::Event::TextEntered:
        {
            for (int i = 0; i < sizeof(m_allTextBoxes) / sizeof(m_allTextBoxes[0]); i++)
            {
                if(m_allTextBoxes[i].getSelected())
                    m_allTextBoxes[i].typedOn(event);
            }
            break;
        }
       
        case sf::Event::MouseMoved:
        {
            if (m_signInButton.isMouseOver(*m_context->m_window))
            {
                m_signInButton.setTextColor(sf::Color(190, 190, 190));
            }
            else
            {
                m_signInButton.setTextColor(sf::Color::White);
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
            if (m_signInButton.isMouseOver(*m_context->m_window))
            {
                m_signInButton.setTextColor(sf::Color::White);
                if (verified)
                {
                    m_context->m_states->add(std::make_unique<MainMenu>(m_context), true);
                }
                else
                {
                    std::cout << "Error login, wrong info" << std::endl;
                }
            }
            else
            {
                m_signInButton.setTextColor(sf::Color::White);
            }

            if (m_allTextBoxes[0].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(true);
                m_allTextBoxes[1].setSelected(false);
                m_allTextBoxes[2].setSelected(false);
            }
            else if (m_allTextBoxes[1].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(false);
                m_allTextBoxes[1].setSelected(true);
                m_allTextBoxes[2].setSelected(false);
            }
            else if (m_allTextBoxes[2].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(false);
                m_allTextBoxes[1].setSelected(false);
                m_allTextBoxes[2].setSelected(true);
            }
        default:
            break;
        }
    }
}

void LoginPageState::update(sf::Time deltaTime)
{
    if (m_allTextBoxes[0].getText() == jsonFile["username"] && m_allTextBoxes[1].getText() == jsonFile["email"] && m_allTextBoxes[2].getText() == jsonFile["pwd"])
    {
        verified = true;
    }
}

void LoginPageState::draw()
{
	m_context->m_window->clear();
    m_context->m_window->draw(m_loginBackground);
    m_context->m_window->draw(m_signInTitle);
    m_context->m_window->draw(m_userNameTitle);
    m_context->m_window->draw(m_emailIDTitle);
    m_context->m_window->draw(m_passwordTitle);

    for (int i = 0; i < sizeof(m_allTextBoxes)/sizeof(m_allTextBoxes[0]); i++)
    {
        m_allTextBoxes[i].Draw(*m_context->m_window);
    }
	m_signInButton.Draw(*m_context->m_window);
	m_context->m_window->display();
}

void LoginPageState::start()
{
}

void LoginPageState::pause()
{
}
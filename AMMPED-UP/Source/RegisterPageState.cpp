#include "../Header Files/RegisterPageState.h"
#include "../Header Files/LoginState.h"

RegisterPageState::RegisterPageState(std::shared_ptr<Context>& context) :
	m_context(context)
{
    file = std::ofstream("key.json");
}

RegisterPageState::~RegisterPageState()
{
}

void RegisterPageState::init()
{
	m_context->m_assets->addFont(LOGIN_FONT, "Resources/fonts/Arial.ttf");
	
	//BACKGROUND 
	m_context->m_assets->addTextures(MENU_BACKGROUND, "Resources/assets/login.png");
	m_loginBackground.setTexture(m_context->m_assets->getTexture(MENU_BACKGROUND));
	m_loginBackground.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);
	m_loginBackground.setOrigin(sf::Vector2f(m_loginBackground.getTexture()->getSize().x / 2, m_loginBackground.getTexture()->getSize().y / 2));
    m_loginBackground.setScale({ 2,2 });

	//SIGN UP TITLE
	m_signUpTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_signUpTitle.setString("SIGN UP");
	m_signUpTitle.setCharacterSize(35);
	m_signUpTitle.setOrigin(m_signUpTitle.getLocalBounds().width / 2, m_signUpTitle.getLocalBounds().height / 2);
	m_signUpTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 230.0f);

	//USERNAME TITLE
	m_userNameTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_userNameTitle.setString("Username");
	m_userNameTitle.setCharacterSize(25);
	m_userNameTitle.setOrigin(m_userNameTitle.getLocalBounds().width / 2, m_userNameTitle.getLocalBounds().height / 2);
	m_userNameTitle.setPosition(m_context->m_window->getSize().x / 4 + 2, m_context->m_window->getSize().y / 2 - 200.0f);

	//USERNAME TEXTBOX
	m_allTextBoxes[0] = Textbox({ 400,25 }, 20, sf::Color::Black, sf::Color::Transparent, sf::Color::White, true);
	m_allTextBoxes[0].setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_allTextBoxes[0].setPosition(sf::Vector2f(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 - 170.0f));


	//EMAIL TITLE
	m_emailIDTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_emailIDTitle.setString("Email");
	m_emailIDTitle.setCharacterSize(25);
	m_emailIDTitle.setOrigin(m_emailIDTitle.getLocalBounds().width / 2, m_emailIDTitle.getLocalBounds().height / 2);
	m_emailIDTitle.setPosition(m_context->m_window->getSize().x / 4 - m_emailIDTitle.getGlobalBounds().width / 2 + 7, m_context->m_window->getSize().y / 2 - 120.0f);

	//EMAIL TEXTBOX
	m_allTextBoxes[1] = Textbox({ 400,25 }, 20, sf::Color::Black, sf::Color::Transparent, sf::Color::White, false);
	m_allTextBoxes[1].setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_allTextBoxes[1].setPosition(sf::Vector2f(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 - 90.0f));

    //CONFIRM EMAIL TITLE
    m_confirmEmailIDTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_confirmEmailIDTitle.setString("Confirm Email");
    m_confirmEmailIDTitle.setCharacterSize(25);
    m_confirmEmailIDTitle.setOrigin(m_confirmEmailIDTitle.getLocalBounds().width / 2, m_confirmEmailIDTitle.getLocalBounds().height / 2);
    m_confirmEmailIDTitle.setPosition(m_context->m_window->getSize().x / 4 + m_confirmEmailIDTitle.getGlobalBounds().width / 4 - 14, m_context->m_window->getSize().y / 2 - 40);

    //CONFIRM EMAIL TEXTBOX
    m_allTextBoxes[2] = Textbox({ 400,25 }, 20, sf::Color::Black, sf::Color::Transparent, sf::Color::White, false);
    m_allTextBoxes[2].setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_allTextBoxes[2].setPosition(sf::Vector2f(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 -10.0f));

    //PASSWORD TITTLE
    m_passwordTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_passwordTitle.setString("Password");
    m_passwordTitle.setCharacterSize(25);
    m_passwordTitle.setOrigin(m_passwordTitle.getLocalBounds().width / 2, m_passwordTitle.getLocalBounds().height / 2);
    m_passwordTitle.setPosition(m_context->m_window->getSize().x / 4, m_context->m_window->getSize().y / 2 + 40.0f);

    //PASSWORD TEXTBOX
    m_allTextBoxes[3] = Textbox({ 400,25 }, 20, sf::Color::Black, sf::Color::Transparent, sf::Color::White, false);
    m_allTextBoxes[3].setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_allTextBoxes[3].setPosition(sf::Vector2f(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 + 70.0f));

	//CONFIRM PASSWORD TITTLE
    m_confirmPasswordTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_confirmPasswordTitle.setString("Confirm Password");
    m_confirmPasswordTitle.setCharacterSize(25);
    m_confirmPasswordTitle.setOrigin(m_confirmPasswordTitle.getLocalBounds().width / 2, m_confirmPasswordTitle.getLocalBounds().height / 2);
    m_confirmPasswordTitle.setPosition(m_context->m_window->getSize().x / 4 + m_confirmEmailIDTitle.getGlobalBounds().width / 4 + 10,  m_context->m_window->getSize().y / 2 + 120.0f);

	//CONFIRM PASSWORD TEXTBOX
	m_allTextBoxes[4] = Textbox({ 400,25 }, 20, sf::Color::Black, sf::Color::Transparent, sf::Color::White, false);
	m_allTextBoxes[4].setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_allTextBoxes[4].setPosition(sf::Vector2f(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 + 150.0f));

	//SIGN IN BUTTON
	m_registerButton = Button("Register", { 200,40 }, 35, sf::Color::Green, sf::Color::White);
	m_registerButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_registerButton.setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2 - m_registerButton.getButtonSize().x / 2, m_context->m_window->getSize().y - 30.0f - m_registerButton.getButtonSize().y / 2));
}

void RegisterPageState::processInput()
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
                if (m_allTextBoxes[i].getSelected())
                    m_allTextBoxes[i].typedOn(event);
            }

            break;
        }

        case sf::Event::MouseMoved:
        {
            if (m_registerButton.isMouseOver(*m_context->m_window))
            {
                m_registerButton.setTextColor(sf::Color(190, 190, 190));
            }
            else
            {
                m_registerButton.setTextColor(sf::Color::White);
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
            if (m_registerButton.isMouseOver(*m_context->m_window))
            {
                m_registerButton.setTextColor(sf::Color::White);
                
                m_context->m_states->add(std::make_unique<LoginState>(m_context), true);
                jsonFile["username"] = m_allTextBoxes[0].getText();
                jsonFile["email"] = m_allTextBoxes[2].getText();
                jsonFile["pwd"] = m_allTextBoxes[3].getText();
                file << jsonFile;
            }
            else
            {
                m_registerButton.setTextColor(sf::Color::White);
            }

            if (m_allTextBoxes[0].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(true);
                m_allTextBoxes[1].setSelected(false);
                m_allTextBoxes[2].setSelected(false);
                m_allTextBoxes[3].setSelected(false);
                m_allTextBoxes[4].setSelected(false);

            }
            else if (m_allTextBoxes[1].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(false);
                m_allTextBoxes[1].setSelected(true);
                m_allTextBoxes[2].setSelected(false);
                m_allTextBoxes[3].setSelected(false);
                m_allTextBoxes[4].setSelected(false);

            }
            else if (m_allTextBoxes[2].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(false);
                m_allTextBoxes[1].setSelected(false);
                m_allTextBoxes[2].setSelected(true);
                m_allTextBoxes[3].setSelected(false);
                m_allTextBoxes[4].setSelected(false);

            }
            else if (m_allTextBoxes[3].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(false);
                m_allTextBoxes[1].setSelected(false);
                m_allTextBoxes[2].setSelected(false);
                m_allTextBoxes[3].setSelected(true);
                m_allTextBoxes[4].setSelected(false);

            }
            else if (m_allTextBoxes[4].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(false);
                m_allTextBoxes[1].setSelected(false);
                m_allTextBoxes[2].setSelected(false);
                m_allTextBoxes[3].setSelected(false);
                m_allTextBoxes[4].setSelected(true);

            }
        default:
            break;
        }
    }
}

void RegisterPageState::update(sf::Time deltaTime)
{
    
}

void RegisterPageState::draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_loginBackground);
    m_context->m_window->draw(m_signUpTitle);
    m_context->m_window->draw(m_userNameTitle);
    m_context->m_window->draw(m_emailIDTitle);
    m_context->m_window->draw(m_confirmEmailIDTitle);
    m_context->m_window->draw(m_passwordTitle);
    m_context->m_window->draw(m_confirmPasswordTitle);


    for (int i = 0; i < sizeof(m_allTextBoxes) / sizeof(m_allTextBoxes[0]); i++)
    {
        m_allTextBoxes[i].Draw(*m_context->m_window);
    }
    m_registerButton.Draw(*m_context->m_window);
    m_context->m_window->display();
}

void RegisterPageState::start()
{
}

void RegisterPageState::pause()
{
}

void RegisterPageState::input()
{
}

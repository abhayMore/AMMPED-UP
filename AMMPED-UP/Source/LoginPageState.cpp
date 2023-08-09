#include "../Header Files/LoginPageState.h"
#include "../Header Files/MainMenu.h"
#include "../Header Files/LoginState.h"

LoginPageState::LoginPageState(std::shared_ptr<Context>& context) :
    m_context(context)
{
    m_username = UserNameManager::getInstance();
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
    m_signInTitle.setOutlineThickness(1);

	//USERNAME TITLE
	m_userNameTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_userNameTitle.setString("Username OR Email ID");
	m_userNameTitle.setCharacterSize(25);
	m_userNameTitle.setOrigin(m_userNameTitle.getLocalBounds().width / 2, m_userNameTitle.getLocalBounds().height / 2);
	m_userNameTitle.setPosition(m_context->m_window->getSize().x / 4 + 77, m_context->m_window->getSize().y / 2 - 80.0f);

	//USERNAME TEXTBOX
    m_allTextBoxes[0] = Textbox({ 400,25 },20, sf::Color::Black, sf::Color::Transparent,sf::Color::White, true);
    m_allTextBoxes[0].setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_allTextBoxes[0].setPosition(sf::Vector2f( m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 - 50.0f ));

	//PASSWORD TITTLE
	m_passwordTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_passwordTitle.setString("Password");
	m_passwordTitle.setCharacterSize(25);
	m_passwordTitle.setOrigin(m_passwordTitle.getLocalBounds().width / 2, m_passwordTitle.getLocalBounds().height / 2);
	m_passwordTitle.setPosition(m_context->m_window->getSize().x / 4, m_context->m_window->getSize().y / 2);

	//PASSWORD TEXTBOX
    m_allTextBoxes[1] = Textbox({ 400,25 }, 20, sf::Color::Black, sf::Color::Transparent, sf::Color::White, false);
    m_allTextBoxes[1].setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_allTextBoxes[1].setPosition(sf::Vector2f(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 + 30.0f));

	//SIGN IN BUTTON
	m_signInButton = Button("Sign In",{ 150,50 }, 35, sf::Color::Green, sf::Color::White);
	m_signInButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_signInButton.setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2 - m_signInButton.getButtonSize().x / 2 - 150, m_context->m_window->getSize().y - 200.0f - m_signInButton.getButtonSize().y / 2));
    m_signInButton.setBackColor(sf::Color::Transparent);
    m_signInButton.setOutlineThickness(1);

    //BACK BUTTON to transition to previous state ->LoginState
    m_backButton = Button("Back", { 150,50 }, 35, sf::Color::Green, sf::Color::White);
    m_backButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
    m_backButton.setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2 - m_backButton.getButtonSize().x / 2 + 150, m_context->m_window->getSize().y - 200.0f - m_backButton.getButtonSize().y / 2));
    m_backButton.setBackColor(sf::Color::Transparent);
    m_backButton.setOutlineThickness(1);

    //PROMPTS for exceptions at top left corner
    m_errorPrompt.setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_errorPrompt.setFillColor(sf::Color(255, 49, 49));
    m_errorPrompt.setOutlineThickness(0.5);
    m_errorPrompt.setOutlineColor(sf::Color::Black);
    m_errorPrompt.setString("");
    m_errorPrompt.setCharacterSize(20);
    m_errorPrompt.setOrigin(m_errorPrompt.getLocalBounds().width / 2, m_errorPrompt.getLocalBounds().height / 2);
    m_errorPrompt.setPosition(m_errorPrompt.getLocalBounds().width / 2 + 2, m_errorPrompt.getLocalBounds().height / 2 + 2);
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
        case sf::Event::KeyPressed:
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
            {
                m_isSignInButtonPressed = true;
                break;
            }
            default:
                break;
            }
            break;
        }
        case sf::Event::KeyReleased:
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
            {
                m_isSignInButtonPressed = false;
                m_signInButton.setTextColor(sf::Color::White);

                break;
            }
            default:
                break;
            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            if (m_signInButton.isMouseOver(*m_context->m_window))
            {
                m_signInButton.setTextColor(sf::Color::Magenta);
            }
            else
            {
                m_signInButton.setTextColor(sf::Color::White);
            }
            if (m_backButton.isMouseOver(*m_context->m_window))
            {
                m_backButton.setTextColor(sf::Color::Magenta);
            }
            else
            {
                m_backButton.setTextColor(sf::Color::White);
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (m_backButton.isMouseOver(*m_context->m_window))
            {
                m_isBackButtonPressed = true;
            }
            if (m_signInButton.isMouseOver(*m_context->m_window))
            {  
                m_isSignInButtonPressed = true;
            }
            if (m_allTextBoxes[0].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(true);
                m_allTextBoxes[1].setSelected(false);
            }
            else if (m_allTextBoxes[1].isMouseOver(*m_context->m_window))
            {
                m_allTextBoxes[0].setSelected(false);
                m_allTextBoxes[1].setSelected(true);
            }
            break;
        }
        default:
            break;
        }
    }
}

void LoginPageState::update(sf::Time deltaTime)
{
    m_elapsedTime += deltaTime;
    if (m_isSignInButtonPressed)
    {    
        m_signInButton.setTextColor(sf::Color::Magenta);
        const auto loginData = m.findDocument(m_allTextBoxes[0].getText());
        if (anyTextboxEmpty())
        {
            m_errorPrompt.setString("Error, empty values");
            m_elapsedTime = sf::Time(sf::milliseconds(0));
        }
        else if((std::get<0>(loginData) == m_allTextBoxes[0].getText() || std::get<1>(loginData) == m_allTextBoxes[0].getText()) && std::get<2>(loginData) == m_allTextBoxes[1].getText())
        {
            verified = true;
            m_username->setUsername(std::get<0>(loginData));
        }
        else
        {
            m_errorPrompt.setString("Error login, invalid username or password");
        }
        m_isSignInButtonPressed = false;
    }
    

    if (verified == true)
    {
        m_context->m_states->add(std::make_unique<MainMenu>(m_context), true);
        verified = false;
    }
    if (m_isBackButtonPressed)
    {
        m_backButton.setTextColor(sf::Color::Magenta);
        m_context->m_states->popCurrent();
        m_context->m_states->add(std::make_unique<LoginState>(m_context), true);
        m_isBackButtonPressed = false;
    }

    if (m_elapsedTime.asSeconds() > 3.0)
    {
        m_errorPrompt.setString("");
        m_elapsedTime = sf::Time::Zero;
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
    m_context->m_window->draw(m_errorPrompt);

    for (int i = 0; i < 2; i++)
    {
        m_allTextBoxes[i].Draw(*m_context->m_window);
    }
	m_signInButton.Draw(*m_context->m_window);
    m_backButton.Draw(*m_context->m_window);
	m_context->m_window->display();
}

void LoginPageState::start()
{
}

void LoginPageState::pause()
{
}

bool LoginPageState::anyTextboxEmpty()
{
    for (auto& textbox : m_allTextBoxes) {
        if (textbox.getText() == "") {
            return true;
        }
    }
    return false;
}

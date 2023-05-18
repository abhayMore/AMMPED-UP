#include "../Header Files/LoginPageState.h"
#include "../Header Files/MainMenu.h"
#include "../Header Files/LoginState.h"

LoginPageState::LoginPageState(std::shared_ptr<Context>& context) :
	m_context(context)
{
    inputFile = std::ifstream("key.json");
    if (inputFile.is_open() && inputFile.peek() != std::ifstream::traits_type::eof())
    {
        jsonFile = nlohmann::json::parse(inputFile);
        inputFile.close();
    }
    else
    {
        fileEmpty = true;
    }
    outputFile = std::ofstream("key.json");
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

    //BACK BUTTON to transition to previous state ->LoginState
    m_backButton = Button("Back", { 150,50 }, 35, sf::Color::Green, sf::Color::White);
    m_backButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
    m_backButton.setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2 - m_backButton.getButtonSize().x / 2 + 150, m_context->m_window->getSize().y - 200.0f - m_backButton.getButtonSize().y / 2));
    m_backButton.setBackColor(sf::Color::Transparent);

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
            if (!fileEmpty)
                writeToFile();
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
            if (m_backButton.isMouseOver(*m_context->m_window))
            {
                m_backButton.setTextColor(sf::Color(190, 190, 190));
            }
            else
            {
                m_backButton.setTextColor(sf::Color::White);
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
            if (m_backButton.isMouseOver(*m_context->m_window))
            {
                m_backButton.setTextColor(sf::Color(190, 190, 190));
                m_isBackButtonPressed = true;
            }
            if (m_signInButton.isMouseOver(*m_context->m_window))
            {
                m_signInButton.setTextColor(sf::Color::White);
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
        default:
            break;
        }
    }
}

void LoginPageState::update(sf::Time deltaTime)
{
    if (m_isSignInButtonPressed)
    {
        if (fileEmpty == false) {
            for (const auto& person : jsonFile)
            {
                std::hash<std::string> pwd_hash;
                auto hashedPWD = pwd_hash(m_allTextBoxes[1].getText());
                if ((m_allTextBoxes[0].getText() == person["username"].get<std::string>() ||
                    m_allTextBoxes[0].getText() == person["email"].get<std::string>()) &&
                    hashedPWD == person["pwd"])
                {
                    verified = true;
                    m_username->setUsername(m_allTextBoxes[0].getText());
                    break;
                }                                
            }
        }
        else
        {
            m_errorPrompt.setString("User not found, did you register?");
        }
        if(fileEmpty == false && verified == false)
        {
            m_errorPrompt.setString("Error login, invalid username or password");
        }
        m_isSignInButtonPressed = false;
    }
    if (verified == true)
    {
        m_context->m_states->add(std::make_unique<MainMenu>(m_context), true);
        verified = false;
        outputFile << std::setw(4) << jsonFile << std::endl;
        outputFile.close();
    }
    if (m_isBackButtonPressed)
    {
        if (fileEmpty == false)
            writeToFile();
        m_context->m_states->popCurrent();
        m_context->m_states->add(std::make_unique<LoginState>(m_context), true);
        m_isBackButtonPressed = false;
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

void LoginPageState::writeToFile()
{
    outputFile << std::setw(4) << jsonFile << std::endl;
    outputFile.close();
}
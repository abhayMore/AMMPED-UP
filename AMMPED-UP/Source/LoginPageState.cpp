#include "../Header Files/LoginPageState.h"
#include "../Header Files/MainMenu.h"
#include "../Header Files/LoginState.h"

enum buttonValues
{
    SIGN_IN,
    BACK
};

enum textboxValues
{
    UID,
    PWD
};

LoginPageState::LoginPageState(std::shared_ptr<Context>& context) :
    m_context(context), m_errorPrompt(*m_context->m_window),
    gui(*m_context->m_window)
{
    theme.load("Resources/Black.txt");
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
    m_loginBackground.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2));
    m_loginBackground.setOrigin(sf::Vector2f(static_cast<float>(m_loginBackground.getTexture()->getSize().x / 2), static_cast<float>(m_loginBackground.getTexture()->getSize().y / 2)));
    m_loginBackground.setScale({ 2,2 });

	//SIGN IN TITLE
    m_signInTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
    m_signInTitle.setString("SIGN IN");
    m_signInTitle.setCharacterSize(35);
    m_signInTitle.setOrigin(m_signInTitle.getLocalBounds().width / 2, m_signInTitle.getLocalBounds().height / 2);
    m_signInTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 175.0f);
    m_signInTitle.setOutlineThickness(1);

	//USERNAME TITLE
	m_userNameTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_userNameTitle.setString("Username OR Email ID");
	m_userNameTitle.setCharacterSize(25);
	m_userNameTitle.setOrigin(m_userNameTitle.getLocalBounds().width / 2, m_userNameTitle.getLocalBounds().height / 2);
	m_userNameTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 4) + 77.0f, static_cast<float>(m_context->m_window->getSize().y / 2) - 80.0f);

	//PASSWORD TITTLE
	m_passwordTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_passwordTitle.setString("Password");
	m_passwordTitle.setCharacterSize(25);
	m_passwordTitle.setOrigin(m_passwordTitle.getLocalBounds().width / 2, m_passwordTitle.getLocalBounds().height / 2);
	m_passwordTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 4), static_cast<float>(m_context->m_window->getSize().y / 2));


    //////////////////////////////////////////////////
    m_context->m_assets->addGuiFont(MAIN_FONT, "Resources/fonts/BungeeSpice-Regular.TTF");
    m_context->m_assets->addGuiFont(LOGIN_FONT, "Resources/fonts/Arial.ttf");

    for (int i = 0; i < 2; i++)
    {
        m_editTextBoxes[i] = tgui::EditBox::create();
        m_editTextBoxes[i]->getRenderer()->setFont(m_context->m_assets->getGuiFont(LOGIN_FONT));
        m_editTextBoxes[i]->setSize(400, 25);
        m_editTextBoxes[i]->setTextSize(20);
        m_editTextBoxes[i]->getRenderer()->setTextColor(tgui::Color::White);
        m_editTextBoxes[i]->getRenderer()->setBorderColor(tgui::Color::Black);
        m_editTextBoxes[i]->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
        m_editTextBoxes[i]->getRenderer()->setBorderColorFocused(tgui::Color::White);
        if (i == UID)
        {
            m_editTextBoxes[i]->setFocused(true);
            m_editTextBoxes[i]->setPosition(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 - 50.0f);
            m_editTextBoxes[i]->getRenderer()->setBackgroundColorFocused(tgui::Color(0, 0, 0, 120));
        }
        else if (i == PWD)
        {
            m_editTextBoxes[i]->setPasswordCharacter('*');
            m_editTextBoxes[i]->setPosition(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 + 30.0f);
            m_editTextBoxes[i]->getRenderer()->setBackgroundColorFocused(tgui::Color(0, 0, 0, 120));

        }
        gui.add(m_editTextBoxes[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        m_pageButtons[i] = tgui::Button::create();
        m_pageButtons[i]->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
        m_pageButtons[i]->getRenderer()->setBorderColor(tgui::Color::Transparent);
        m_pageButtons[i]->getRenderer()->setTextColor(tgui::Color::White);
        m_pageButtons[i]->getRenderer()->setFont(tgui::Font(m_context->m_assets->getGuiFont(MAIN_FONT).getId()));
        m_pageButtons[i]->setTextSize(35);
        
        if (i == SIGN_IN)
        {
            m_pageButtons[i]->setText("Sign In");
            m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2 - 150.0f, m_context->m_window->getSize().y / 2 + 200.0f);
            m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
            m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
        }
        else if (i == BACK)
        {
            m_pageButtons[i]->setText("Back");
            m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2 + 150.0f, m_context->m_window->getSize().y / 2 + 200.0f);
            m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
            m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
        }
        m_pageButtons[i]->getRenderer()->setTextOutlineThickness(1);
        gui.add(m_pageButtons[i]);
    }
	

    //PROMPTS for exceptions at top left corner
    m_context->m_assets->addGuiFont(LOGIN_FONT, "Resources/fonts/Arial.ttf");

    //PROMPTS for exceptions at top left corner
    m_errorPrompt.init(
        "",
        m_context->m_assets->getGuiFont(LOGIN_FONT),
        20,
        { 2,2 },
        { m_errorPrompt.getSize().x / 2, m_errorPrompt.getSize().y / 2 },
        sf::Color(255, 49, 49),
        0.5,
        sf::Color::Black
    );

}

void LoginPageState::processInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        //gui.handleEvent(event);
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            m_context->m_window->close();
            break;
        }
        case sf::Event::KeyPressed:
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Tab:
            {
                if (m_editTextBoxes[0]->isFocused())
                {
                    m_editTextBoxes[0]->setFocused(false);
                    m_editTextBoxes[1]->setFocused(true);
                }
                else if (m_editTextBoxes[1]->isFocused())
                {
                    m_editTextBoxes[1]->setFocused(false);
                    m_pageButtons[0]->setFocused(true);
                }
                else if (m_pageButtons[0]->isFocused())
                {
                    m_pageButtons[0]->setFocused(false);
                    m_pageButtons[1]->setFocused(true);
                }
                else if (m_pageButtons[1]->isFocused())
                {
                    m_pageButtons[1]->setFocused(false);
                    m_editTextBoxes[0]->setFocused(true);
                }
                else
                {
                    m_editTextBoxes[0]->setFocused(true);
                }
                break;
            }
            case sf::Keyboard::Enter:
            {
                float mouseX = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x);
                float mouseY = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y);
                if (m_pageButtons[0]->isFocused() || m_pageButtons[0]->isMouseOnWidget({mouseX, mouseY}))
                {
                    m_isSignInButtonPressed = true;
                }
                if (m_pageButtons[1]->isFocused() || m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_isBackButtonPressed = true;
                }
                m_isSignInButtonPressed = true;
                break;
            }
            case sf::Keyboard::Escape:
            {
                m_isBackButtonPressed = true;
                break;
            }
            default:
                break;
            }
            break;
        }
        case sf::Event::TextEntered:
        {
            if ((event.text.unicode != '\n') && (event.text.unicode != '\t') && (event.text.unicode != '\r'))
            {           
                float mouseX = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x);
                float mouseY = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y);
                if (m_editTextBoxes[0]->isFocused())
                {
                    if (event.text.unicode == '\b') // Backspace
                    {
                        m_editTextBoxes[0]->setText(m_editTextBoxes[0]->getText().substr(0, m_editTextBoxes[0]->getText().size() - 1));
                    }
                    else if (event.text.unicode < 128) // Regular character
                    {
                        m_editTextBoxes[0]->setText(m_editTextBoxes[0]->getText() + static_cast<char>(event.text.unicode));
                    }
                }
                if (m_editTextBoxes[1]->isFocused())
                {
                    if (event.text.unicode == '\b') // Backspace
                    {
                        m_editTextBoxes[1]->setText(m_editTextBoxes[1]->getText().substr(0, m_editTextBoxes[1]->getText().size() - 1));
                    }
                    else if (event.text.unicode < 128) // Regular character
                    {
                        m_editTextBoxes[1]->setText(m_editTextBoxes[1]->getText() + static_cast<char>(event.text.unicode));
                    }
                }
            }


            break;
        }
        case sf::Event::MouseMoved:
        {
            float mouseX = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x);
            float mouseY = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y);
            if (m_pageButtons[0]->isMouseOnWidget({ mouseX, mouseY }))
            {
                m_pageButtons[0]->getRenderer()->setTextColor(sf::Color::Magenta);
                m_pageButtons[1]->setFocused(false);

            }
            if(!m_pageButtons[0]->isMouseOnWidget({ mouseX, mouseY }))
            {
                m_pageButtons[0]->getRenderer()->setTextColor(sf::Color::White);

            }
            if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
            {
                m_pageButtons[1]->getRenderer()->setTextColor(sf::Color::Magenta);
                m_pageButtons[0]->setFocused(false);

            }
            if(!m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
            {
                m_pageButtons[1]->getRenderer()->setTextColor(sf::Color::White);
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            switch (event.key.code)
            {
            case sf::Mouse::Left:
            {
                float mouseX = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x);
                float mouseY = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y);
                if (m_pageButtons[0]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_isSignInButtonPressed = true;
                    m_editTextBoxes[0]->setFocused(false);
                    m_editTextBoxes[1]->setFocused(false);
                }
                if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_isBackButtonPressed = true;
                }

                //TEXTBOXES             
                if (m_editTextBoxes[0]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_editTextBoxes[0]->setFocused(true);
                    m_editTextBoxes[1]->setFocused(false);
                    m_pageButtons[0]->setFocused(false);
                    m_pageButtons[1]->setFocused(false);
                }
                if (m_editTextBoxes[1]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_editTextBoxes[1]->setFocused(true);
                    m_editTextBoxes[0]->setFocused(false);
                    m_pageButtons[0]->setFocused(false);
                    m_pageButtons[1]->setFocused(false);
                }
                break;
            }
            default:
                break;
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
    if (m_isSignInButtonPressed)
    {   

        std::string temp(m_editTextBoxes[0]->getText());
        const auto loginData = m.findDocument(temp);
        if (anyTextboxEmpty())
        {
            m_errorPrompt.setText("Error, empty values");
            m_elapsedTime = sf::Time(sf::milliseconds(0));
        }
        else if((std::get<0>(loginData) == m_editTextBoxes[0]->getText() || std::get<1>(loginData) == m_editTextBoxes[0]->getText()) && std::get<2>(loginData) == m_editTextBoxes[1]->getText())
        {
            verified = true;
            m_username->setUsername(std::get<0>(loginData));
        }
        else
        {
            m_errorPrompt.setText("Error login, invalid username or password");
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
        m_context->m_states->popCurrent();
        m_context->m_states->add(std::make_unique<LoginState>(m_context), true);
        m_isBackButtonPressed = false;
    }

    if (m_errorPrompt.getLength() > 2)
    {
        m_elapsedTime += deltaTime;
        if (m_elapsedTime.asSeconds() > 3.0)
        {
            m_errorPrompt.setText("");
            m_elapsedTime = sf::Time::Zero;
        }
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
    m_errorPrompt.draw();

    for (int i = 0; i < 2; i++)
    {
        //m_allTextBoxes[i].Draw(*m_context->m_window);
    }
    gui.draw();
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
    for (auto& textbox : m_editTextBoxes) {
        if (textbox->getText() == "") {
            return true;
        }
    }
    return false;
}

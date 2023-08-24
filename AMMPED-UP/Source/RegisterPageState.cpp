#include "../Header Files/RegisterPageState.h"
#include "../Header Files/LoginState.h"

enum buttonValues
{
    REGISTER,
    BACK
};

enum textboxValues
{
    UID,
    EID,
    CEID,
    PWD,
    CPWD
};


bool isEmailValid(const std::string& email)
{
    // Regular expression pattern for email validation
    std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    // Check if the email matches the pattern
    if (!std::regex_match(email, pattern)) {
        std::cout << "Invalid email format." << std::endl;
        return false;
    }

    // Check if the email contains a domain
    std::size_t atIndex = email.find('@');
    if (atIndex == std::string::npos) {
        std::cout << "Missing '@' symbol in email." << std::endl;
        return false;
    }

    // Check if the domain is empty
    std::size_t dotIndex = email.find('.', atIndex + 1);
    if (dotIndex == std::string::npos || dotIndex == atIndex + 1) {
        std::cout << "Missing domain in email." << std::endl;
        return false;
    }

    // Check if the domain has valid characters
    std::string domain = email.substr(atIndex + 1, dotIndex - atIndex - 1);
    std::regex domainPattern(R"([a-zA-Z0-9.-]+)");
    if (!std::regex_match(domain, domainPattern)) {
        std::cout << "Invalid characters in domain." << std::endl;
        return false;
    }

    // Check if the domain has a valid top-level domain (TLD)
    std::string tld = email.substr(dotIndex + 1);
    std::regex tldPattern(R"([a-zA-Z]{2,})");
    if (!std::regex_match(tld, tldPattern)) {
        std::cout << "Invalid top-level domain (TLD)." << std::endl;
        return false;
    }

    // Email is valid
    return true;
}


RegisterPageState::RegisterPageState(std::shared_ptr<Context>& context) :
    m_context(context), m_errorPrompt(*m_context->m_window),
    gui(*m_context->m_window)

{
    theme.load("Resources/Black.txt");
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
	m_loginBackground.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2));
	m_loginBackground.setOrigin(sf::Vector2f(static_cast<float>(m_loginBackground.getTexture()->getSize().x / 2), static_cast<float>(m_loginBackground.getTexture()->getSize().y / 2)));
    m_loginBackground.setScale({ 2,2 });

	//SIGN UP TITLE
	m_signUpTitle.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_signUpTitle.setString("SIGN UP");
	m_signUpTitle.setCharacterSize(35);
	m_signUpTitle.setOrigin(m_signUpTitle.getLocalBounds().width / 2, m_signUpTitle.getLocalBounds().height / 2);
	m_signUpTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 2), static_cast<float>(m_context->m_window->getSize().y / 2) - 230.0f);
    m_signUpTitle.setOutlineThickness(1);

	//USERNAME TITLE
	m_userNameTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_userNameTitle.setString("Username");
	m_userNameTitle.setCharacterSize(25);
	m_userNameTitle.setOrigin(m_userNameTitle.getLocalBounds().width / 2, m_userNameTitle.getLocalBounds().height / 2);
	m_userNameTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 4) + 2.0f, static_cast<float>(m_context->m_window->getSize().y / 2) - 200.0f);

	//EMAIL TITLE
	m_emailIDTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
	m_emailIDTitle.setString("Email");
	m_emailIDTitle.setCharacterSize(25);
	m_emailIDTitle.setOrigin(m_emailIDTitle.getLocalBounds().width / 2, m_emailIDTitle.getLocalBounds().height / 2);
	m_emailIDTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 4) - static_cast<float>(m_emailIDTitle.getGlobalBounds().width / 2) + 7.0f, static_cast<float>(m_context->m_window->getSize().y / 2) - 120.0f);
	
    //CONFIRM EMAIL TITLE
    m_confirmEmailIDTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_confirmEmailIDTitle.setString("Confirm Email");
    m_confirmEmailIDTitle.setCharacterSize(25);
    m_confirmEmailIDTitle.setOrigin(m_confirmEmailIDTitle.getLocalBounds().width / 2, m_confirmEmailIDTitle.getLocalBounds().height / 2);
    m_confirmEmailIDTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 4) + static_cast<float>(m_confirmEmailIDTitle.getGlobalBounds().width / 4) - 14.0f, static_cast<float>(m_context->m_window->getSize().y / 2) - 40.0f);
   
    //PASSWORD TITTLE
    m_passwordTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_passwordTitle.setString("Password");
    m_passwordTitle.setCharacterSize(25);
    m_passwordTitle.setOrigin(m_passwordTitle.getLocalBounds().width / 2, m_passwordTitle.getLocalBounds().height / 2);
    m_passwordTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 4), static_cast<float>(m_context->m_window->getSize().y / 2) + 40.0f);
   
	//CONFIRM PASSWORD TITTLE
    m_confirmPasswordTitle.setFont(m_context->m_assets->getFont(LOGIN_FONT));
    m_confirmPasswordTitle.setString("Confirm Password");
    m_confirmPasswordTitle.setCharacterSize(25);
    m_confirmPasswordTitle.setOrigin(m_confirmPasswordTitle.getLocalBounds().width / 2, m_confirmPasswordTitle.getLocalBounds().height / 2);
    m_confirmPasswordTitle.setPosition(static_cast<float>(m_context->m_window->getSize().x / 4) + static_cast<float>(m_confirmEmailIDTitle.getGlobalBounds().width / 4) + 10.0f, static_cast<float>(m_context->m_window->getSize().y / 2) + 120.0f);
	
    ////////////////////////////////
    m_context->m_assets->addGuiFont(MAIN_FONT, "Resources/fonts/BungeeSpice-Regular.TTF");
    m_context->m_assets->addGuiFont(LOGIN_FONT, "Resources/fonts/Arial.ttf");

    for (int i = 0; i < 5; i++)
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
            m_editTextBoxes[i]->setPosition(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 - 170.0f);
            m_editTextBoxes[i]->getRenderer()->setBackgroundColorFocused(tgui::Color(0, 0, 0, 120));
        }
        else if (i == EID)
        {
            m_editTextBoxes[i]->setPosition(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 - 90.0f);
            m_editTextBoxes[i]->getRenderer()->setBackgroundColorFocused(tgui::Color(0, 0, 0, 120));

        }
        else if (i == CEID)
        {
            m_editTextBoxes[i]->setPosition(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 - 10.0f);
            m_editTextBoxes[i]->getRenderer()->setBackgroundColorFocused(tgui::Color(0, 0, 0, 120));

        }
        else if (i == PWD)
        {
            m_editTextBoxes[i]->setPasswordCharacter('*');
            m_editTextBoxes[i]->setPosition(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 + 70.0f);
            m_editTextBoxes[i]->getRenderer()->setBackgroundColorFocused(tgui::Color(0, 0, 0, 120));

        }
        else if (i == CPWD)
        {
            m_editTextBoxes[i]->setPasswordCharacter('*');
            m_editTextBoxes[i]->setPosition(m_context->m_window->getSize().x / 4 - 50, m_context->m_window->getSize().y / 2 + 150.0f);
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

        if (i == REGISTER)
        {
            m_pageButtons[i]->setText("Register");
            m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2 - 150.0f, m_context->m_window->getSize().y - 200.0f);
            m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
            m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
        }
        else if (i == BACK)
        {
            m_pageButtons[i]->setText("Back");
            m_pageButtons[i]->setPosition(m_context->m_window->getSize().x / 2 - m_pageButtons[i]->getSize().x / 2 + 150.0f, m_context->m_window->getSize().y - 200.0f);
            m_pageButtons[i]->getRenderer()->setTextColorFocused(tgui::Color::Magenta);
            m_pageButtons[i]->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
        }
        m_pageButtons[i]->getRenderer()->setTextOutlineThickness(1);
        gui.add(m_pageButtons[i]);
    }


    //PROMPTS for exceptions at top left corner
    m_context->m_assets->addGuiFont(LOGIN_FONT, "Resources/fonts/Arial.ttf");

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
                    m_editTextBoxes[2]->setFocused(true);
                }
                else if (m_editTextBoxes[2]->isFocused())
                {
                    m_editTextBoxes[2]->setFocused(false);
                    m_editTextBoxes[3]->setFocused(true);

                }
                else if (m_editTextBoxes[3]->isFocused())
                {
                    m_editTextBoxes[3]->setFocused(false);
                    m_editTextBoxes[4]->setFocused(true);
                }
                else if (m_editTextBoxes[4]->isFocused())
                {
                    m_editTextBoxes[4]->setFocused(false);
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
                if (m_pageButtons[0]->isFocused() || m_pageButtons[0]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_isRegisterButtonPressed = true;
                }
                if (m_pageButtons[1]->isFocused() || m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_isBackButtonPressed = true;
                }
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
            if (event.text.unicode != '\t' && event.text.unicode != '\n')
            {
                float mouseX = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x);
                float mouseY = static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y);
                for (int i = 0; i < 5; i++)
                {
                    if (m_editTextBoxes[i]->isFocused())
                    {
                        if (event.text.unicode == '\b') // Backspace
                        {
                            m_editTextBoxes[i]->setText(m_editTextBoxes[i]->getText().substr(0, m_editTextBoxes[i]->getText().size() - 1));
                        }
                        else if (event.text.unicode < 128) // Regular character
                        {
                            m_editTextBoxes[i]->setText(m_editTextBoxes[i]->getText() + static_cast<char>(event.text.unicode));
                        }
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
            if (!m_pageButtons[0]->isMouseOnWidget({ mouseX, mouseY }))
            {
                m_pageButtons[0]->getRenderer()->setTextColor(sf::Color::White);

            }
            if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
            {
                m_pageButtons[1]->getRenderer()->setTextColor(sf::Color::Magenta);
                m_pageButtons[0]->setFocused(false);

            }
            if (!m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
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
                    m_isRegisterButtonPressed = true;
                    for (int i = 0; i < 5; i++)
                    {
                        m_editTextBoxes[i]->setFocused(false);
                    }
                }
                if (m_pageButtons[1]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_isBackButtonPressed = true;
                }

                if (m_editTextBoxes[0]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_editTextBoxes[0]->setFocused(true);
                    m_editTextBoxes[1]->setFocused(false);
                    m_editTextBoxes[2]->setFocused(false);
                    m_editTextBoxes[3]->setFocused(false);
                    m_editTextBoxes[4]->setFocused(false);
                    m_pageButtons[0]->setFocused(false);
                    m_pageButtons[1]->setFocused(false);
                }
                if (m_editTextBoxes[1]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_editTextBoxes[1]->setFocused(true);
                    m_editTextBoxes[0]->setFocused(false);
                    m_editTextBoxes[2]->setFocused(false);
                    m_editTextBoxes[3]->setFocused(false);
                    m_editTextBoxes[4]->setFocused(false);
                    m_pageButtons[0]->setFocused(false);
                    m_pageButtons[1]->setFocused(false);
                }
                if (m_editTextBoxes[2]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_editTextBoxes[2]->setFocused(true);
                    m_editTextBoxes[0]->setFocused(false);
                    m_editTextBoxes[1]->setFocused(false);
                    m_editTextBoxes[3]->setFocused(false);
                    m_editTextBoxes[4]->setFocused(false);
                    m_pageButtons[0]->setFocused(false);
                    m_pageButtons[1]->setFocused(false);
                }
                if (m_editTextBoxes[3]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_editTextBoxes[3]->setFocused(true);
                    m_editTextBoxes[0]->setFocused(false);
                    m_editTextBoxes[1]->setFocused(false);
                    m_editTextBoxes[2]->setFocused(false);
                    m_editTextBoxes[4]->setFocused(false);
                    m_pageButtons[0]->setFocused(false);
                    m_pageButtons[1]->setFocused(false);
                }
                if (m_editTextBoxes[4]->isMouseOnWidget({ mouseX, mouseY }))
                {
                    m_editTextBoxes[4]->setFocused(true);
                    m_editTextBoxes[0]->setFocused(false);
                    m_editTextBoxes[1]->setFocused(false);
                    m_editTextBoxes[2]->setFocused(false);
                    m_editTextBoxes[3]->setFocused(false);
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


void RegisterPageState::update(sf::Time deltaTime)
{
    if (m_isRegisterButtonPressed)
    {
        if (anyTextboxEmpty())
        {
            m_errorPrompt.setText("Error, empty values");
            resetTextboxes();
        }
        else 
        {
            //--------------//
            if (m_editTextBoxes[1]->getText() != m_editTextBoxes[2]->getText())
            {
                m_errorPrompt.setText("Email ID does not match!!");
                resetTextboxes();
            }
            else if (!isEmailValid(std::string(m_editTextBoxes[2]->getText())))
            {
                m_errorPrompt.setText("Email is invalid!!");
                resetTextboxes();
            }

            //------PWD DOES NOT MATCH CASE--------//
            if (m_editTextBoxes[3]->getText() != m_editTextBoxes[4]->getText())
            {
                m_errorPrompt.setText("Password do not match!!");
                resetTextboxes();
            }
            //-----IS DATA PRESENT IN ONLINE DATABASE CASE---------//
            if (m.isDataPresent("username", std::string(m_editTextBoxes[0]->getText())))
            {
                isUsernameTaken = true;
                if (m.isDataPresent("email", std::string(m_editTextBoxes[2]->getText())))
                {
                    isUserExists = true;
                }
            }
            else if (m.isDataPresent("email", std::string(m_editTextBoxes[2]->getText())))
            {
                isEmailRegistered = true;
            }


            if (isUserExists)
            {
                m_errorPrompt.setText("User already exists. Please login!!");
                isUserExists = false;

                resetTextboxes();
            }
            else if (isUsernameTaken && !isEmailRegistered)
            {
                m_errorPrompt.setText("Username is already taken. Please choose another username!!");
                isUsernameTaken = false;
                resetTextboxes();
            }
            else if (!isUsernameTaken && isEmailRegistered)
            {
                m_errorPrompt.setText("Email is already registered. Please use a different email!!");
                isEmailRegistered = false;
                resetTextboxes();
            }

            else if (!isUserExists && !isUsernameTaken && !isEmailRegistered)
            {
                if (!anyTextboxEmpty())
                {
                    registerUser();
                }
            }
            if (!anyTextboxEmpty())
            {
                registerUser();
            }
        }
        m_isRegisterButtonPressed = false;
    }

    if (registered)
    {
        m_context->m_states->add(std::make_unique<LoginState>(m_context), true);
        registered = false;
    }
    if (m_isBackButtonPressed)
    {
        m_context->m_states->popCurrent();
        m_context->m_states->add(std::make_unique<LoginState>(m_context), true);
        m_isBackButtonPressed = false;
    }

    if (m_errorPrompt.getLength() > 2 )
    {
        m_elapsedTime += deltaTime;
        if (m_elapsedTime.asSeconds() > 3.0)
        {
            m_errorPrompt.setText("");
            m_elapsedTime = sf::Time::Zero;
        }
    }
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
    gui.draw(); 
    m_errorPrompt.draw();
    m_context->m_window->display();
}

void RegisterPageState::start()
{
}

void RegisterPageState::pause()
{
}

void RegisterPageState::registerUser()
{
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::v_noabi::document::value doc_value =
        builder << "username" << std::string(m_editTextBoxes[0]->getText())
        << "email" << std::string(m_editTextBoxes[2]->getText())
        << "pwd" << std::string(m_editTextBoxes[4]->getText())
        << "score" << 0
        << bsoncxx::builder::stream::finalize;
    m.insertDocument(doc_value);

    registered = true;
    resetTextboxes();
}

void RegisterPageState::resetTextboxes()
{
    for (auto& textbox : m_editTextBoxes)
    {
        textbox->setText("");
    }
}

bool RegisterPageState::anyTextboxEmpty()
{
    for (auto& textbox : m_editTextBoxes) {
        if (textbox->getText() == "") {
            return true;
        }
    }
    return false;
}


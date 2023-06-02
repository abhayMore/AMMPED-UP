#include "../Header Files/RegisterPageState.h"
#include "../Header Files/LoginState.h"

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
    m_context(context), instance(MongoInstance::getInstance())
{
    
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
	m_registerButton = Button("Register", { 200,40 }, 30, sf::Color::Green, sf::Color::White);
	m_registerButton.setFont(m_context->m_assets->getFont(MAIN_FONT));
	m_registerButton.setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2 - m_registerButton.getButtonSize().x / 2 - 150, m_context->m_window->getSize().y - 200.0f - m_registerButton.getButtonSize().y / 2));
    m_registerButton.setBackColor(sf::Color::Transparent);

    //BACK BUTTON to transition to previous state ->LoginState
    m_backButton = Button("Back", { 200,40 }, 30, sf::Color::Green, sf::Color::White);
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
        {
            if (m_backButton.isMouseOver(*m_context->m_window))
            {
                m_backButton.setTextColor(sf::Color(190, 190, 190));
                m_isBackButtonPressed = true;
            }
            if (m_registerButton.isMouseOver(*m_context->m_window))
            {
                m_registerButton.setTextColor(sf::Color(190, 190, 190));
                
                if (m_allTextBoxes[1].getText() != m_allTextBoxes[2].getText())
                {
                    m_errorPrompt.setString("Email ID does not match!!");
                    resetTextboxes();
                }
                if (!isEmailValid(m_allTextBoxes[2].getText()))
                {
                    m_errorPrompt.setString("Email is invalid!!");
                    resetTextboxes();
                }
                if (m_allTextBoxes[3].getText() != m_allTextBoxes[4].getText())
                {
                    m_errorPrompt.setString("Password do not match!!");
                    resetTextboxes();
                }
                //--------------//
                if (m.isDataPresent("username", m_allTextBoxes[0].getText()))
                {
                    isUsernameTaken = true;
                    if (m.isDataPresent("email", m_allTextBoxes[2].getText()))
                    {
                        isUserExists = true;
                    }
                }
                else if (m.isDataPresent("email", m_allTextBoxes[2].getText()))
                {
                    isEmailRegistered = true;
                }
                if (isUserExists)
                {
                    m_errorPrompt.setString("User already exists. Please login!!");
                    resetTextboxes();
                }
                else if (isUsernameTaken && !isEmailRegistered)
                {
                    m_errorPrompt.setString("Username is already taken. Please choose another username!!");
                    resetTextboxes();
                }
                else if (!isUsernameTaken && isEmailRegistered)
                {
                    m_errorPrompt.setString("Email is already registered. Please use a different email!!");
                    resetTextboxes();
                }
                else if (!isUserExists && !isUsernameTaken && !isEmailRegistered)
                {
                    if (!anyTextboxEmpty())
                    {
                        registerUser();
                    }
                }
                isUsernameTaken = false;
                isEmailRegistered = false;
                isUserExists = false;


                if (!anyTextboxEmpty())
                {
                    registerUser();
                }

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
            break;
        }
        default:
            break;
        }
    }
}


void RegisterPageState::update(sf::Time deltaTime)
{
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
    m_context->m_window->draw(m_errorPrompt);


    for (int i = 0; i < sizeof(m_allTextBoxes) / sizeof(m_allTextBoxes[0]); i++)
    {
        m_allTextBoxes[i].Draw(*m_context->m_window);
    }
    m_registerButton.Draw(*m_context->m_window);
    m_backButton.Draw(*m_context->m_window);
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
        builder << "username" << m_allTextBoxes[0].getText()
        << "email" << m_allTextBoxes[2].getText()
        << "pwd" << m_allTextBoxes[4].getText()
        << "score" << 0
        << bsoncxx::builder::stream::finalize;
    m.insertDocument(doc_value);

    registered = true;
    resetTextboxes();
}

void RegisterPageState::resetTextboxes()
{
    for (auto& textbox : m_allTextBoxes)
    {
        textbox.setString("");
    }
}

bool RegisterPageState::anyTextboxEmpty()
{
    for (auto& textbox : m_allTextBoxes) {
        if (textbox.getText() == "") {
            return true;
        }
    }
    return false;
}


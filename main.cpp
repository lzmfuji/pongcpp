#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong the Game");

    // Carregar a fonte
    sf::Font font;

    !font.loadFromFile("karmat.ttf");

    if (!font.loadFromFile("karmat.ttf")) {
        std::cout << "Erro ao carregar a fonte!" << std::endl;
        return -1;
     }

    int player1Score = 0;
    int player2Score = 0;

    // ScoreBoard Player 1
    sf::Text player1Text;
    player1Text.setFont(font);
    player1Text.setCharacterSize(20); // Tamanho da fonte
    player1Text.setFillColor(sf::Color::Red); // Cor do texto

    // Centralizar o texto na tela Player 1
    sf::FloatRect player1textRec = player1Text.getLocalBounds();
    player1Text.setPosition(sf::Vector2f(10, 560));

    // ScoreBoard Player 2
    sf::Text player2Text;
    player2Text.setFont(font);
    player2Text.setCharacterSize(20); // Tamanho da fonte
    player2Text.setFillColor(sf::Color::Blue); // Cor do texto

    // Centralizar o texto na tela Player 2
    sf::FloatRect player2textRec = player2Text.getLocalBounds();
    player2Text.setPosition(sf::Vector2f(660, 560));


    // Cria raquete do Player 1
    sf::RectangleShape player1(sf::Vector2f(10, 100));
    player1.setPosition(10, 250);
    player1.setFillColor(sf::Color::Red);

    // Cria raquete do Player 2
    sf::RectangleShape player2(sf::Vector2f(10, 100));
    player2.setPosition(780, 250);
    player2.setFillColor(sf::Color::Blue);

    // Cria a bola
    sf::CircleShape ball(10);
    ball.setPosition(395, 295);
    ball.setFillColor(sf::Color::White);

    // Cria PowerUp
    sf::RectangleShape power(sf::Vector2f(50, 50));
    power.setFillColor(sf::Color::Yellow);
    bool showPower = false;

    // Define a velocidade da bola
    float ballSpeedX = -0.03f, ballSpeedY = -0.03f;
    float playerSpeed = 0.2f;
    bool powerUpSpawned = false;


    // Loop do game
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed: " << event.key.code << std::endl;
            }
        }

        // Movimento dos jogadores
        // PLAYER 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player1.getPosition().y > 0)
            player1.move(0, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player1.getPosition().y < 500)
            player1.move(0, playerSpeed);

        // PLAYER 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player2.getPosition().y > 0)
            player2.move(0, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player2.getPosition().y < 500)
            player2.move(0, playerSpeed);


        // Movimento da bola e Pontuacao
        ball.move(ballSpeedX, ballSpeedY);

        if (ball.getPosition().y <= 0)
            {
                ballSpeedY = -ballSpeedY;
            }

        else if (ball.getPosition().y >= 590)
        {
                ballSpeedY = -ballSpeedY;

        }

        // Esse IF faz a validação se a bola ultrapassou a parede adversaria
        player1Text.setString("Score: " + std::to_string(player1Score));
        if (ball.getPosition().x >= 790)
        {
            player1Score++;
        }

        player2Text.setString("Score: " + std::to_string(player2Score));
        if (ball.getPosition().x <= 0)
        {
            player2Score++;
        }


        // Esse IF faz a validação se a bola bateu na raquete, aqui vamos alterar para fazer o https://github.com/marchiore/pongcpp/issues/5
        if (ball.getGlobalBounds().intersects(player1.getGlobalBounds()) || 
            ball.getGlobalBounds().intersects(player2.getGlobalBounds())) {
            ballSpeedX =- ballSpeedX;
            
        }

        if (ball.getPosition().x <= 0 || ball.getPosition().x >= 790) {
            ballSpeedX =- ballSpeedX;
        }


        if (ball.getPosition().y <= 0 || ball.getPosition().y >= 790) {
            ballSpeedY =+ ballSpeedY;
        }

        //  PowerUp aparece apos condicao de pontuacao
        if ((player1Score > 3 && player2Score > 3) && !powerUpSpawned)
        {
            showPower = true;
            powerUpSpawned = true;
            power.setPosition(395, 295);
        }

        //  Efeito do PowerUp apos interseccao com a bola
        if (showPower && ball.getGlobalBounds().intersects(power.getGlobalBounds()))
        {
            showPower = false; // PowerUp desaparece
            player1.setSize(sf::Vector2f(10, 150));
            player2.setSize(sf::Vector2f(10, 150));
        }

        //  Velocidade da Bola aumenta apos condicao de pontuacao
        if (player1Score >= 5 && player2Score >= 5)
        {
            ball.move(ballSpeedX * 1.2f, ballSpeedY * 1.2f);
        }


        // Desenho
        window.clear();
        window.draw(player1Text);
        window.draw(player2Text);
        window.draw(ball);
        if (showPower) {
            window.draw(power); // Draw the power-up only if it's supposed to be visible
        }
        window.draw(player1);
        window.draw(player2);

        // window.draw(text); // Desenhar o texto na tela
        window.display();
    }

    return 0;
}

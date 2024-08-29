#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong the Game");

    // Carregar a fonte
    sf::Font font;

    // !font.loadFromFile("arial.ttf")

    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        std::cout << "Erro ao carregar a fonte!" << std::endl;
        return -1;
    }

    // Criar o texto
    sf::Text text;
    text.setFont(font);
    text.setString("Lais Pong!");
    text.setCharacterSize(50); // Tamanho da fonte
    text.setFillColor(sf::Color::White); // Cor do texto

    // Centralizar o texto na tela
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(800 / 2.0f, 600 / 2.0f));

    // Raquetes e bola
    sf::RectangleShape player1(sf::Vector2f(10, 100));
    player1.setPosition(10, 250);
    player1.setFillColor(sf::Color::White);

    sf::RectangleShape player2(sf::Vector2f(10, 100));
    player2.setPosition(780, 250);
    player2.setFillColor(sf::Color::White);

    sf::CircleShape ball(10);
    ball.setPosition(395, 295);
    ball.setFillColor(sf::Color::White);

    float ballSpeedX = -0.08f, ballSpeedY = -0.08f;
    float playerSpeed = 0.2f;

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

        // Movimento da bola
        ball.move(ballSpeedX, ballSpeedY);

        if (ball.getPosition().y <= 0 || ball.getPosition().y >= 590)
            ballSpeedY = -ballSpeedY;

        if (ball.getGlobalBounds().intersects(player1.getGlobalBounds()) || 
            ball.getGlobalBounds().intersects(player2.getGlobalBounds())) {
            ballSpeedX = -ballSpeedX;
        }

        if (ball.getPosition().x <= 0 || ball.getPosition().x >= 790) {
            ball.setPosition(395, 295);
            ballSpeedX = -ballSpeedX;
        }
        
        // Desenho
        window.clear();
        window.draw(player1);
        window.draw(player2);
        window.draw(ball);
        window.draw(text); // Desenhar o texto na tela
        window.display();
    }

    return 0;
}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "menu.h"


int main() {

    bool isPlaying = false;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong the Game");

    Menu menu(window.getSize().x, window.getSize().y);

    // Carregar a fonte
    sf::Font font;

    !font.loadFromFile("karmat.ttf");

    if (!font.loadFromFile("karmat.ttf")) {
        std::cout << "Erro ao carregar a fonte!" << std::endl;
        return -1;
     }

    // Carregar Som de Collide
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("collide.wav")) 
    {
         std::cout << "ERROR" << std::endl;
    }
    sf::Sound collide;
    collide.setBuffer(buffer);

    // Carregar Som de Score
    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("score.wav")) 
    {
         std::cout << "ERROR" << std::endl;
    }
    sf::Sound score;
    score.setBuffer(buffer2);

    // Carregar Som do PowerUp
    sf::SoundBuffer buffer3;
    if (!buffer3.loadFromFile("powerup.wav")) 
    {
         std::cout << "ERROR" << std::endl;
    }
    sf::Sound powerup;
    powerup.setBuffer(buffer3);

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

        if (!isPlaying) {
            switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            menu.MoveUp();
                            break;
                        case sf::Keyboard::Down:
                            menu.MoveDown();
                            break;
                        case sf::Keyboard::Return:
                            switch (menu.GetPressedItem()) {
                                case 0: // Play selected
                                    std::cout << "Play button has been pressed" << std::endl;
                                    isPlaying = true; // Set game state to playing
                                    break;
                                case 1: // Save selected
                                    std::cout << "Save button has been pressed" << std::endl;
                                    break;
                                case 2: // Exit selected
                                    std::cout << "Exit button has been pressed" << std::endl;
                                    window.close();
                                    break;
                            }
                            break;
                    }
            }
        } else {
            // Handle game events here (like player movement, etc.)
            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed: " << event.key.code << std::endl;
            }
        }
    }

     // Clear the window
    window.clear();

    if (!isPlaying) {
        // Draw the menu when the game is not playing
        menu.draw(window);
    } else {
        // Game logic only runs when isPlaying is true

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

        // Verifica se a bola ultrapassou a parede
        player1Text.setString("Score: " + std::to_string(player1Score));
        if (ball.getPosition().x >= 790)
        {
            player1Score++;
            score.play();
        }

        player2Text.setString("Score: " + std::to_string(player2Score));
        if (ball.getPosition().x <= 0)
        {
            player2Score++;
            score.play();
        }

        // Verifica se a bola bateu na raquete
        if (ball.getGlobalBounds().intersects(player1.getGlobalBounds()) || 
            ball.getGlobalBounds().intersects(player2.getGlobalBounds())) {
            collide.play();
            ballSpeedX =- ballSpeedX;
        }

        if (ball.getPosition().x <= 0 || ball.getPosition().x >= 790) {
            ballSpeedX =- ballSpeedX;
        }

        if (ball.getPosition().y <= 0 || ball.getPosition().y >= 790) {
            ballSpeedY =+ ballSpeedY;
        }

        // PowerUp aparece apos condicao de pontuacao
        if ((player1Score > 2 && player2Score > 2) && !powerUpSpawned)
        {
            showPower = true;
            powerUpSpawned = true;
            power.setPosition(395, 295);
        }

        // Efeito do PowerUp apos interseccao com a bola
        if (showPower && ball.getGlobalBounds().intersects(power.getGlobalBounds()))
        {
            showPower = false; // PowerUp desaparece
            powerup.play();
            player1.setSize(sf::Vector2f(10, 150));
            player2.setSize(sf::Vector2f(10, 150));
        }

        // Velocidade da Bola aumenta apos condicao de pontuacao
        if (player1Score >= 5 && player2Score >= 5)
        {
            ball.move(ballSpeedX * 1.2f, ballSpeedY * 1.2f);
        }

        // Desenho do jogo
        window.draw(player1Text);
        window.draw(player2Text);
        window.draw(ball);
        if (showPower) {
            window.draw(power); // Draw the power-up only if it's supposed to be visible
        }
        window.draw(player1);
        window.draw(player2);
    }

    // Display everything
    window.display();
}
}

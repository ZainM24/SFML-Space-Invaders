#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>


void startAliens(sf::Sprite alienArray[55]) {
    int num = 0;
    for (int i=0; i<5; i++) {
        for (int j=0; j<11; j++) {
            alienArray[num].setPosition(j*75+15, i*50);
            num++;
        }
    }
}

//--------------------------------------------------------------------

int main()
{
    srand(time(NULL));

    // Variables
    bool loss = false;
    bool win = false;
    bool powerdown = true;
    bool active = false;
    bool pow = false;

    bool ok = true;
    bool eok = true;
    bool okStart = true;
    sf::Clock clock;
    int fnum = 0;
    bool check = false;
    double speed = 0.05;
    int score = 0;


    // Create the main window
    sf::RenderWindow app(sf::VideoMode(1200, 800), "Space Invaders");

    // Load a sprite to display
    sf::Texture texture;
    texture.loadFromFile("resources/spaceInvadersSpriteSheet.png");


    sf::IntRect rectSource1(0,0,75,50);
    sf::IntRect rectSource2(0,60,75,50);
    sf::IntRect rectSource3(155,0,50,50);

    sf::Sprite alienArray[55];
    int num = 0;
    for (int i=0; i<5; i++) {
        for (int j=0; j<11; j++) {
            if (i==2 || i==1) {

                alienArray[num].setTexture(texture);
                alienArray[num].setTextureRect(rectSource1);
                alienArray[num].setOrigin(75/2, 50/2);
                alienArray[num].setPosition(j*75+15, i*50-1000);

            } else if (i==4 || i==3) {

                alienArray[num].setTexture(texture);
                alienArray[num].setTextureRect(rectSource2);
                alienArray[num].setOrigin(75/2, 50/2);
                alienArray[num].setPosition(j*75+15, i*50-1000);

            } else {

                alienArray[num].setTexture(texture);
                alienArray[num].setTextureRect(rectSource3);
                alienArray[num].setOrigin(50/2, 50/2);
                alienArray[num].setPosition(j*75+15, i*50-1000);

            }

            num++;
        }
    }


    sf::IntRect rectSourceShip(75,320,45,35);

    sf::Sprite ship(texture);
    ship.setTextureRect(rectSourceShip);
    ship.setOrigin(22, 18);
    ship.setPosition(-600, 750);

    sf::RectangleShape bullet;
    bullet.setSize(sf::Vector2f(10, 50));
    bullet.setOrigin(5, 5);
    bullet.setPosition(-500, 50);

    sf::IntRect rectSourceExplosion(180,320,45,35);
    sf::Sprite explosion(texture);
    explosion.setTextureRect(rectSourceExplosion);
    explosion.setOrigin(22, 18);
    explosion.setPosition(-5000,500);


    // Loading obstacle/power-down sprite
    sf::Texture bombTexture;
    bombTexture.loadFromFile("bomb.png");
    sf::IntRect bombRect(10, 10, 200, 200);
    sf::Sprite power(bombTexture);
    power.setTextureRect(bombRect);
    power.setOrigin(75, 75);
    power.setPosition(rand()%1200, -300);


    // Loading win, lose, and score text
    sf::Font siFont;
    siFont.loadFromFile("resources/space_invaders.ttf");

    sf::Text winText;
    winText.setFont(siFont);
    winText.setString("                   You win!\nPress (R) to play again.");
    winText.setCharacterSize(32);
    winText.setPosition(-5000, 400);

    sf::Text loseText;
    loseText.setFont(siFont);
    loseText.setString("           You lose!\nPress (R) to retry.");
    loseText.setCharacterSize(32);
    loseText.setPosition(-5000, 400);

    sf::Text scoreCount;
    scoreCount.setFont(siFont);
    scoreCount.setString("Score:");
    scoreCount.setCharacterSize(32);
    scoreCount.setPosition(20, 20);

    sf::Text scoreText;
    scoreText.setFont(siFont);
    scoreText.setString(std::to_string(score));
    scoreText.setCharacterSize(32);
    scoreText.setPosition(180, 20);


    // Loading main menu assets
    sf::IntRect rectSourceOpen(230,250,60,50);
    sf::Sprite welcome(texture);
    welcome.setTextureRect(rectSourceOpen);
    welcome.setOrigin(30, 25);
    welcome.setPosition(600,200);
    welcome.setScale(7.f,7.f);

    sf::Text welcomeText;
    welcomeText.setFont(siFont);
    welcomeText.setString("Play Space Invaders");
    welcomeText.setCharacterSize(32);
    welcomeText.setPosition(380, 500);

    sf::Text pressStart;
    pressStart.setFont(siFont);
    pressStart.setString("(Press the space bar to start)");
    pressStart.setCharacterSize(20);
    pressStart.setPosition(380, 700);


    // Loading sounds
    sf::SoundBuffer bgSoundBuff;
    bgSoundBuff.loadFromFile("resources/backgroundSong.wav");
    sf::Sound bgSound;
    bgSound.setBuffer(bgSoundBuff);

    sf::SoundBuffer shotBuff;
    shotBuff.loadFromFile("resources/shot.wav");
    sf::Sound shotSound;
    shotSound.setBuffer(shotBuff);
    shotSound.setVolume(25.f);

    sf::SoundBuffer explosionBuff;
    explosionBuff.loadFromFile("resources/explosion.wav");
    sf::Sound boom;
    boom.setBuffer(explosionBuff);
    boom.setVolume(10.f);


	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Game loop
        explosion.move(speed, 0);
        for (int i=0; i<55; i++) {
            alienArray[i].move(speed, 0);
            for (int f = 0; f < 11; f++) {
            if (alienArray[f].getGlobalBounds().intersects(bullet.getGlobalBounds())) {
                explosion.setPosition(sf::Vector2f(alienArray[f].getPosition().x, alienArray[f].getPosition().y));
                std::cout << "Explosion is " << alienArray[f].getPosition().x << std::endl;
                boom.play();
                alienArray[f].move(1000,-1800);
                bullet.move(0,-800);
                ok=true;
                eok=false;
                score+=15;
                scoreText.setString(std::to_string(score));
                std::cout << "Score is " << score << std::endl;
                }
            }
            for (int t = 11; t < 33; t++) {
            if (alienArray[t].getGlobalBounds().intersects(bullet.getGlobalBounds())) {
                explosion.setPosition(sf::Vector2f(alienArray[t].getPosition().x, alienArray[t].getPosition().y));
                std::cout << "Explosion is " << alienArray[t].getPosition().x << std::endl;
                boom.play();
                alienArray[t].move(1000,-1800);
                bullet.move(0,-800);
                ok=true;
                eok=false;
                score+=10;
                scoreText.setString(std::to_string(score));
                std::cout << "Score is " << score << std::endl;
                }
            }
            for (int v = 32; v < 55; v++) {
            if (alienArray[v].getGlobalBounds().intersects(bullet.getGlobalBounds())) {
                explosion.setPosition(sf::Vector2f(alienArray[v].getPosition().x, alienArray[v].getPosition().y));
                std::cout << "Explosion is " << alienArray[v].getPosition().x << std::endl;
                boom.play();
                alienArray[v].move(1000,-1800);
                bullet.move(0,-800);
                ok=true;
                eok=false;
                score+=5;
                scoreText.setString(std::to_string(score));
                std::cout << "Score is " << score << std::endl;
                }
            }
            if (alienArray[i].getPosition().x >1180 || alienArray[i].getPosition().x < 15  ) {
                if (alienArray[i].getPosition().y >0) {
                    check = true;
                }
            }
        }
        if (check) {
            speed *= -1;
            for (int i=0; i<55; i++) {
                alienArray[i].move(0,40);
            }
            check = false;
        }


        if (clock.getElapsedTime().asSeconds() >.50f) {
            if (eok == false) {
                explosion.move(0, -800);
                eok = true;
            }

            if (fnum == 0) {
                rectSource1.left +=75;
                rectSource2.left +=75;
                rectSource3.left +=55;
                fnum = 1;
            } else if (fnum==1) {
                rectSource1.left -=75;
                rectSource2.left -=75;
                rectSource3.left -=55;
                fnum = 0;
            }
            for (int i=0; i<55; i++) {
                if(i<11) {
                    alienArray[i].setTextureRect(rectSource3);
                } else if (i>10 && i<33) {
                    alienArray[i].setTextureRect(rectSource2);
                }  else {
                    alienArray[i].setTextureRect(rectSource1);
                }
            }
            clock.restart();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ship.getPosition().x > 22) {
            ship.move(-.5,0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& ship.getPosition().x < 1180) {
            ship.move(.5,0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) {
            if (okStart == false && ok == true) {
                shotSound.play();
                bullet.setPosition(sf::Vector2f(ship.getPosition().x, ship.getPosition().y));
                ok = false;
            }
            else if (okStart == true) {
                welcome.move(-1200, 0);
                welcomeText.move(-1200, 0);
                pressStart.move(-1200, 0);
                okStart = false;
                startAliens(alienArray);
                ship.setPosition(600, 750);
                speed = .1;
                bgSound.play();
                bgSound.setLoop(true);
            }
        }


        if (ok == false) {
            bullet.move(0,-1);
            if (bullet.getPosition().y <-45 ) {
                ok = true;
            }
        }


        // Loss/win screens
        for (int p = 0; p < 11; p++) {
            if (alienArray[p].getPosition().y > 800)
            if (score < 495) {
                loss = true;
                score = 0;
                ship.move(0, -1200);
                bgSound.stop();
            }
        }

        if (score >= 495 && loss == false) {
            win = true;
            score = 0;
            scoreText.move(450, 0);
            scoreCount.move(450, 0);
            ship.move(0, -1200);
            }


        // Game restart
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (win == true) {
                winText.setPosition(-1200, 0);
                bullet.setPosition(-1200, 0);
                scoreCount.setPosition(20, 20);
                scoreText.setPosition(180, 20);
                power.setPosition(rand()%1200, -300);
                score = 0;
                scoreText.setString(std::to_string(score));
                startAliens(alienArray);
                ship.setPosition(600, 750);
                speed = .1;
                active = false;
                win = false;
                loss = false;
                pow = false;
            }

            if (loss == true) {
                bgSound.play();
                bgSound.setLoop(true);
                loseText.setPosition(-1200, 0);
                bullet.setPosition(-1200, 0);
                scoreCount.setPosition(20, 20);
                scoreText.setPosition(180, 20);
                power.setPosition(rand()%1200, -300);
                score = 0;
                scoreText.setString(std::to_string(score));
                startAliens(alienArray);
                ship.setPosition(600, 750);
                speed = .1;
                active = false;
                win = false;
                loss = false;
                pow = false;
            }
        }


        // Power-down/obstacle
        /*if (score >= 200 && powerdown == true) {
        power.move(0, 0.085);
        active = true;
        }

        if (ship.getGlobalBounds().intersects(power.getGlobalBounds()) && active == true) {
            pow = true;
            power.move(-5000, -5000);
        }

        if (pow == true) {
            for (int q = 0; q < 55; q++) {
                    alienArray[q].move(speed, 0);
                    }
                }*/


        // Clear screen
        app.clear();

        // Draw the sprite
        for (int a = 0; a < 55; a++) {
            app.draw(alienArray[a]);
        }
        app.draw(ship);
        app.draw(bullet);
        app.draw(explosion);
        app.draw(welcome);
        app.draw(welcomeText);
        app.draw(pressStart);

        app.draw(winText);
        app.draw(loseText);

        if (win == true) {
            winText.setPosition(350, 400);
        }

        if (loss == true) {
            loseText.setPosition(410, 400);
        }

        if (okStart == false) {
            app.draw(scoreCount);
            app.draw(scoreText);
        }

        app.draw(power);


        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}

#include "Player.h"
#include "Space.h"

int heart = 30;
int score = 0;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Game", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);
    srand(time(NULL));
    Player player;
    Clock clock;
    float deltaTime = 0;

    Texture spaceTexture;
    spaceTexture.loadFromFile("space.png");

    Space space(&spaceTexture, Vector2f(100, 100), Vector2f(200, 100));
    Space space2(&spaceTexture, Vector2f(320, 0), Vector2f(420, 0));
    Space space3(&spaceTexture, Vector2f(550, 100), Vector2f(650, 100));

    Font font;
    font.loadFromFile("CourierPrime.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + to_string(score));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);

    Texture heartTexture;
    heartTexture.loadFromFile("heart.png");
    Sprite hearts[3];
    Vector2f heartStartPos = Vector2f(0, 40);
    for (int i = 0; i < 3; i++)
    {
        hearts[i].setTexture(heartTexture);
        hearts[i].setScale(Vector2f(0.1, 0.1));
        hearts[i].setPosition(heartStartPos + Vector2f(50 * i, 0));
    }
   
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
                window.close();
        }
        player.update(deltaTime);
        space.update(deltaTime, player.bullet, &player.bulletStatus);
        space2.update(deltaTime, player.bullet, &player.bulletStatus);
        space3.update(deltaTime, player.bullet, &player.bulletStatus);
        player.checkHit(space.bullet, &space.bulletStatus);
        player.checkHit(space2.bullet, &space2.bulletStatus);
        player.checkHit(space3.bullet, &space3.bulletStatus);

        scoreText.setString("Score: " + to_string(score));

        if (heart == 0)
        {
            window.close();
        }

        window.clear();
        space.render(&window);
        space2.render(&window);
        space3.render(&window);
        player.render(&window);
        window.draw(scoreText);
        for (int i = 0; i < 3 && i < heart; i++)
        {
            window.draw(hearts[i]);
        }
        window.display();
    }
    return 0;
}
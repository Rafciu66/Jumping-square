#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cmath>
#include <iostream>
#include <optional>
#include <random>
#include <utility> // for std::pair
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

std::pair<sf::Vector2f, sf::Vector2f> resolveCollision(
    const sf::Vector2f& pos1, const sf::Vector2f& vel1, float radius1,
    const sf::Vector2f& pos2, const sf::Vector2f& vel2, float radius2
) {
    sf::Vector2f normal = pos2 - pos1;
    float distance = std::sqrt(normal.x * normal.x + normal.y * normal.y);

   
        if (distance == 0.0f || distance >= radius1 + radius2)
            return { vel1, vel2 };

    sf::Vector2f unitNormal = normal / distance;
    sf::Vector2f unitTangent(-unitNormal.y, unitNormal.x);

    float v1n = unitNormal.x * vel1.x + unitNormal.y * vel1.y;
    float v1t = unitTangent.x * vel1.x + unitTangent.y * vel1.y;

    float v2n = unitNormal.x * vel2.x + unitNormal.y * vel2.y;
    float v2t = unitTangent.x * vel2.x + unitTangent.y * vel2.y;

    float v1nAfter = v2n;
    float v2nAfter = v1n;

    sf::Vector2f v1Final = unitNormal * v1nAfter + unitTangent * v1t;
    sf::Vector2f v2Final = unitNormal * v2nAfter + unitTangent * v2t;

    return { v1Final, v2Final };


}

void falling_ball() {
    auto window = sf::RenderWindow(sf::VideoMode({ 400u, 400u }), "Falling Ball");
    window.setFramerateLimit(60);


    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(250, 100, 50));
    sf::Vector2f position = { 50, 100 };
    sf::Vector2f velocity = { 0.0f, 0.0f };
    float gravity = 0.8f;
    float bounceFactor = 0.9f;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();
        velocity.y += gravity; // Apply gravity
        position += velocity; // Update position
        position.y = std::clamp(position.y, 0.0f, 300.0f); // Keep within bounds
        if (position.y >= 300.0f) { // Check for ground collision
            velocity.y *= -bounceFactor; // Reverse velocity with bounce factor
            position.y = 300.0f; // Reset position to ground level
        }
        shape.setPosition(position);
        window.draw(shape);
        window.display();
    }
}



void run() {
    auto window = sf::RenderWindow(sf::VideoMode({ 400u, 400u }), "CMake SFML Project");
    window.setFramerateLimit(60);


    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(250, 100, 50));
    sf::Vector2f position1 = shape.getPosition();
    sf::Vector2f vector1 = { 0.0f, 0.0f };

    sf::CircleShape shape2(50.f);
    shape2.setFillColor(sf::Color(50, 100, 250));
    sf::Vector2f position2 = { 150.0f, 150.0f };
    sf::Vector2f vector2 = { 0.0f, 0.0f };
    float velocity = 5.0;
    float vel_increment = 0.0f;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            vector1.x = -velocity;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            vector1.x = velocity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            vector1.y = -velocity;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            vector1.y = velocity;

        position1.x += vector1.x;
        position1.y += vector1.y;
        position1.x = std::clamp(position1.x, 0.0f, 300.0f);
        position1.y = std::clamp(position1.y, 0.0f, 300.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            vector2.x = -velocity;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            vector2.x = velocity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            vector2.y = -velocity;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            vector2.y = velocity;

        position2.x += vector2.x;
        position2.y += vector2.y;
        position2.x = std::clamp(position2.x, 0.0f, 300.0f);
        position2.y = std::clamp(position2.y, 0.0f, 300.0f);

        auto [newVector1, newVector2] = resolveCollision(
            position1, vector1, shape.getRadius(),
            position2, vector2, shape2.getRadius()
        );

        vector1 = newVector1;
        vector2 = newVector2;

        if (position2.x == 0.0f || position2.x == 300.0f) {
            vector2.x *= -1; velocity += vel_increment;
        }
        if (position2.y == 0.0f || position2.y == 300.0f) {
            vector2.y *= -1; velocity += vel_increment;
        }
        if (position1.x == 0.0f || position1.x == 300.0f) {
            vector1.x *= -1; velocity += vel_increment;
        }
        if (position1.y == 0.0f || position1.y == 300.0f) {
            vector1.y *= -1; velocity += vel_increment;
        }

        velocity = std::clamp(velocity, 0.0f, 10.0f);

        shape.setPosition(position1);
        shape2.setPosition(position2);

        window.draw(shape);
        window.draw(shape2);
        window.display();
    }
}

void run2() {
    auto window = sf::RenderWindow(sf::VideoMode({ 400u, 400u }), "CMake SFML Project");
    window.setFramerateLimit(60);

    // I'm using a placeholder font name. Make sure your path is correct.
    //sf::Font font;
    sf::Font font("C:\\Users\\mniek\\source\\repos\\silver-waddle\\f.ttf");

    sf::Text text(font);
    text.setString("Hello, SFML!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition({ 100, 100 });

    float x = 0.0f, y = 0.0f;
    sf::Vector2i localPosition;
    sf::RectangleShape rect;
	rect.setFillColor(sf::Color(120, 130, 240, 124));
    while (window.isOpen()) {
        // This line proves you are using SFML 3.0 headers
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        localPosition = sf::Mouse::getPosition(window);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            x = static_cast<float>(localPosition.x);
            y = static_cast<float>(localPosition.y);
        }
        else {
            rect.setSize(sf::Vector2f(localPosition.x - x, localPosition.y - y));
            rect.setPosition({ x, y });

            sf::FloatRect rectBounds = rect.getGlobalBounds();
            sf::FloatRect textBounds = text.getGlobalBounds();

            // *** THE CORRECT SFML 3.0 SYNTAX ***
            if (rectBounds.findIntersection(textBounds)) {
                text.setFillColor(sf::Color::Blue);
            }
            else {
                text.setFillColor(sf::Color::White);
            }

            window.draw(rect);
        }

        window.draw(text);
        window.display();
    }
}

int mapValue(float value, float in_min, float in_max, float out_min, float out_max) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Note: This function is not used by the main game, but kept as you provided it.


int getRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// --- Player Logic ---

struct Movement {
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool isGrounded = false; // Flag to track if the player is on a platform

    const float gravity = 1.0f;
    const float minJumpHeight = 1.0f;
    float jumpHeight = minJumpHeight;
    const float jumpHeightLimit = 20.0f;
    const float jumpHeightIncrement = 0.8f;
    bool loadedJump = false;

    void updateJump() {
        jumpHeight += jumpHeightIncrement;
        jumpHeight = std::clamp(jumpHeight, minJumpHeight, jumpHeightLimit);
        loadedJump = true;
    }

    void performJump() {
        if (loadedJump) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                velocity.x = -10.0f; // Adjusted for better control
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                velocity.x = 10.0f;
            }
            velocity.y = -jumpHeight;
            loadedJump = false;
            jumpHeight = minJumpHeight;
        }
    }

    void goLeft() { velocity.x = -5.0f; }
    void goRight() { velocity.x = 5.0f; }
    void stop() { velocity.x = 0.0f; }
    void applyGravity() { velocity.y += gravity; }
    void updatePosition() { position += velocity; }
};

class Player {
    sf::RectangleShape shape;
    Movement movement;

public:
    Player() {
        shape.setSize(sf::Vector2f(50, 50));
        shape.setFillColor(sf::Color(100, 80, 80));
        shape.setOrigin({ shape.getSize().x / 2.0f, shape.getSize().y });
        movement.position = { 400, 850 };
        shape.setPosition(movement.position);
    }

    void handleInput() {
        // Jumping is only possible if you are on the ground.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && movement.isGrounded) {
            movement.updateJump();
            movement.stop();
			int r = mapValue(movement.jumpHeight, 0, movement.jumpHeightLimit, 100, 230);
            int b = 80;
            int g = 80;
            if (r == 230) { r = 255; b = 10; g = 10; } // Ensure color is visible
			shape.setFillColor(sf::Color(r,b, g)); // Change color to indicate jump is loaded
        }
        else {
            // Perform a jump if one is loaded.
            if (movement.loadedJump) {
                movement.performJump();
				shape.setFillColor(sf::Color(100, 80, 80)); // Reset color after jump
            }
            // Normal walking is ONLY allowed if you are on the ground AND not about to jump.
            else if (movement.isGrounded) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                    movement.goLeft();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                    movement.goRight();
                }
                else {
                    movement.stop();
                }
            }
        }
    }

    void onCollision(const sf::FloatRect& platformBounds) {
        if (movement.velocity.y > 0) { // Only collide when falling
            movement.velocity.y = 0.0f;
            movement.position.y = platformBounds.position.y;
            movement.isGrounded = true; // Set the flag on collision!
        }
    }

    void update() {
        movement.applyGravity();
        movement.updatePosition();
        shape.setPosition(movement.position);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    const sf::FloatRect getGlobalBounds() const {
        return shape.getGlobalBounds();
    }

    // Getter and setter for the grounded state
    bool isGrounded() const { return movement.isGrounded; }
    void setGrounded(bool grounded) { movement.isGrounded = grounded; }

    // Method to move the player manually (used for sticking to platforms)
    void move(float x, float y) {
        movement.position.x += x;
        movement.position.y += y;
    }
};

class Platform {
    sf::RectangleShape shape;

public:
    Platform(sf::Vector2f size, sf::Vector2f position) {
        shape.setSize(size);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    void fall(const float speed, float max_height) {
        // Corrected line: create a Vector2f explicitly.
        shape.move(sf::Vector2f(0.0f, speed));

        if (shape.getPosition().y > max_height) {
            float randX = static_cast<float>(getRandomInt(100, 700));
            shape.setPosition({ randX, -shape.getSize().y });
        }
    }

    const sf::FloatRect getGlobalBounds() const {
        return shape.getGlobalBounds();
    }
};

void runGame() {
	int frameCount = 0;
    unsigned int windowWidth = 800u;
    unsigned int windowHeight = 900u;
    float gameSpeedLimit = 5;
    auto window = sf::RenderWindow(sf::VideoMode({ windowWidth, windowHeight }), "Game");
    window.setFramerateLimit(60);
    sf::Font font("C:\\Users\\mniek\\source\\repos\\silver-waddle\\f.ttf");
    sf::Text text(font);
	text.setString("Press Space to jump, Left/Right to move");
	text.setCharacterSize(24);
	text.setPosition({ static_cast<float>(windowWidth/4),static_cast<float>(windowHeight - 50) });
    text.setFillColor(sf::Color(255,255,255,128));

	sf::Text TimerText(font); 
	TimerText.setCharacterSize(48);
	TimerText.setPosition({ 50, 5 });
	TimerText.setFillColor(sf::Color::Yellow);
	TimerText.setString("Score: 0");

	sf::Text gamespeedText(font);
	gamespeedText.setCharacterSize(48);
	gamespeedText.setPosition({ 400, 5 });
	gamespeedText.setFillColor(sf::Color::Yellow);
	gamespeedText.setString("Game Speed: 1.0");


    Player player;
    std::vector<Platform> platforms;
    platforms.emplace_back(sf::Vector2f(200, 20), sf::Vector2f(300, 850)); // Ground
    platforms.emplace_back(sf::Vector2f(150, 20), sf::Vector2f(300, 700));
    platforms.emplace_back(sf::Vector2f(150, 20), sf::Vector2f(100, 550));
    platforms.emplace_back(sf::Vector2f(150, 20), sf::Vector2f(getRandomInt(20, 630), 400));
    platforms.emplace_back(sf::Vector2f(150, 20), sf::Vector2f(getRandomInt(20, 630), 250));
    platforms.emplace_back(sf::Vector2f(150, 20), sf::Vector2f(getRandomInt(20, 630), 100));

    float gameSpeed = 1.0f;
    const float platformFallSpeed =  0.5f;
	bool gamestarted = false;
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // --- GAME LOGIC ---
        // 1. Handle player input.
        player.handleInput();

        // 2. Update player physics (gravity, velocity, position).
        player.update();

        // 3. Assume the player is in the air.
        player.setGrounded(false);

        // 4. Check for collisions, which may prove the assumption in #3 wrong.
        for (auto& platform : platforms) {
            if (platform.getGlobalBounds().findIntersection(player.getGlobalBounds())) {
                player.onCollision(platform.getGlobalBounds());
            }
        }

        // 5. If player is grounded, "stick" them to moving platforms.
        if (player.isGrounded()) {
            player.move(0.0f, platformFallSpeed * gameSpeed);
        }

        // 6. Update all platforms.
        for (auto& platform : platforms) {
            platform.fall(platformFallSpeed * gameSpeed, windowHeight);
        }

        // --- END OF GAME LOGIC ---

        if (player.getGlobalBounds().position.y > 900.0f) {
            window.close();
        }

        gameSpeed += 0.008f; // Slower speed increase
		gameSpeed = std::clamp(gameSpeed, 1.0f, gameSpeedLimit); // Limit the speed increase
        // --- DRAWING ---
        window.clear();
        player.draw(window);
        for (auto& platform : platforms) {
            platform.draw(window);
        }
		window.draw(text);
        frameCount++;
        if (frameCount % 60 == 0) { // Update timer every second
            int seconds = frameCount / 60;
            if (seconds % 20 == 0) {
                gameSpeedLimit += 5;
            }
            TimerText.setString("Score: " + std::to_string(seconds));
		}

		std::ostringstream gamespeedStream;
		gamespeedStream << std::fixed << std::setprecision(2) << gameSpeed;
		std::string gamespeedStr = gamespeedStream.str();
        gamespeedText.setString("Game Speed: " + gamespeedStr);
		window.draw(gamespeedText);
		window.draw(TimerText);
        if(gamestarted) window.display();
        else {
			sf::Text startText(font);
			startText.setString("Press R to start the game");
			startText.setCharacterSize(64);
			startText.setPosition({ 30.0f, static_cast<float>(windowHeight / 2) });
			startText.setFillColor(sf::Color::Yellow);
			window.draw(startText);
            window.display();
			// Wait for the player to press 'R' to start the game
            while(!gamestarted && window.isOpen()) {
                while (const std::optional<sf::Event> event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>()) {
                        window.close();
                    }
				}   
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                    gamestarted = true;
                }
            }
		}
    }
}

void menu() {
    auto window = sf::RenderWindow(sf::VideoMode({ 400u, 400u }), "Jumping Square Menu");
    window.setFramerateLimit(60);

    // I'm using a placeholder font name. Make sure your path is correct.
    //sf::Font font;
    sf::Font font("C:\\Users\\mniek\\source\\repos\\silver-waddle\\f.ttf");

    sf::Text text(font);
    text.setString("Select app ");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition({ 150, 100 });
    sf::RectangleShape rect1(sf::Vector2f(100, 100));
    sf::RectangleShape rect2(sf::Vector2f(100, 100));
	sf::RectangleShape rect3(sf::Vector2f(100, 100));
	sf::RectangleShape rect4(sf::Vector2f(100, 100));
	sf::Color rectColor(255, 250, 205);
	sf::Color textColor(40, 40, 40);
	sf::Text text1(font);
	sf::Text text2(font);
	sf::Text text3(font);   
	sf::Text text4(font);

	text1.setString("Falling Ball");
	text2.setString("Jumping Square");
	text3.setString("Collision");
	text4.setString("Collision2");

    rect1.setPosition({ 75, 285 });
    rect2.setPosition({ 225, 285 });
	rect3.setPosition({ 75, 170 });
	rect4.setPosition({ 225, 170 });

	text1.setCharacterSize(12);
	text2.setCharacterSize(12);
	text3.setCharacterSize(12);
	text4.setCharacterSize(12);

	text1.setFillColor(textColor);
	text2.setFillColor(textColor);
	text3.setFillColor(textColor);
    text4.setFillColor(textColor);


    rect1.setFillColor(rectColor);
	rect2.setFillColor(rectColor);
	rect3.setFillColor(rectColor);
	rect4.setFillColor(rectColor);

    text1.setPosition(rect1.getPosition() + sf::Vector2f(12, 15));
    text2.setPosition(rect2.getPosition() + sf::Vector2f(2, 15));
    text3.setPosition(rect3.getPosition() + sf::Vector2f(20, 15));
    text4.setPosition(rect4.getPosition() + sf::Vector2f(30, 15));


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
            {
                // The event is a MouseButtonPressed event. mb is a valid pointer.
                // Now check which button.
                if (mb->button == sf::Mouse::Button::Left)
                {
                    // Get the click position directly from the event object.
                    const sf::Vector2f clickPosition = static_cast<sf::Vector2f>(mb->position);

                    // Now check containment with the reliable click position.
                    if (rect1.getGlobalBounds().contains(clickPosition)) {
                        window.close(); // Close the menu before opening the other window
                        falling_ball();
                    }
                    else if (rect2.getGlobalBounds().contains(clickPosition)) {
                        window.close();
                        runGame();
                    }
                    else if (rect3.getGlobalBounds().contains(clickPosition)) {
                        window.close();
                        run2();
                    }
                    else if (rect4.getGlobalBounds().contains(clickPosition)) {
                        window.close();
                        run();
                        // Calling menu() from within menu() can lead to stack overflow.
                        // Here it doesn't do anything useful, so it's best to just ignore the click.
                        // If you wanted to "reset" the menu, you'd handle that logic here.
                    }
                }
            }
        } // End of event loop

        // --- FIX 2: Drawing is done ONCE per frame, outside the event loop ---
        window.clear();
        window.draw(text);
        window.draw(rect1);
        window.draw(rect2);
        window.draw(rect3);
        window.draw(rect4);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.display();
    } // End of while(window.isOpen())
}



int main() {
    //runGame();
    while(1) menu();
    
    return 0;
}
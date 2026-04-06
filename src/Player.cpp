#include"Player.h"
Player::Player() {
	//default settings
	position.x = 0.0f;
	position.y = 0.0f;
	directionX = 1;
	directionY = 1;
	double speedCurrent=0.0f;
	isDashing = 0; 
	isJumping = 0; //is on ground
	isWalking = 0;
	isFalling = 0;
	countJump = 0;
}
Player::~Player() {
	//empty&release (?) &save data
	//sfml can auto clear Sprites
}
void Player::init(std::string texture_name, sf::Vector2f pos, float g) {
	position = pos;
	texture.loadFromFile(texture_name);
//	sprite.setTexture();
	sprite.setPosition(position);
}
void Player::walk(int dir) {
	//put whether walk/dash outside this func
	isWalking = 1;
	directionX = dir;
	speedCurrent.x = speedCommon * directionX;
//below should be in update
//	position.x += speedCurrent.x * deltatime;//does the graphics get done here?(no)

}
void Player::climb(int dir) {
	directionY = dir;
	speedCurrent.y = speedClimb * directionY;
//	position.x += speedCurrent.y * deltatime;
}
void Player::fall() {
//???
//	speedCurrent.y  directionY;
//	position.y += speedCurrent.y * deltatime;
//	isFalling = 1;
//how to solve jumping& this 
}
void Player::dash(int dir){
	directionX = dir;//-1 for left
	isDashing = 1;
//	if (isWalking) {
//		isWalking = 0;
//	}
	speedCurrent.x = speedDash*directionX;
}
void Player::jump(){
	isJumping = 1;
	speedCurrent.y = speedJump;
}
void Player::update(double deltatime) {
	if (isWalking) {
		position.x += speedCurrent.x * deltatime;
	}
	if (isDashing && lengthDash<lengthCanDash) {
		position.x += speedCurrent.x * deltatime;
		lengthDash += speedCurrent.x * deltatime;
	}
	if (isJumping) {
		position.y += speedCurrent.y * deltatime;
		speedCurrent.y -= weight;
	}
}
sf::Sprite getSprite() {
	return sprite;
}

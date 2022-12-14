#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
//------------------------------------------------------------------------------------------------
// Window Config
const unsigned int k_windowWidth = 1200;
const unsigned int k_windowHeight = 800;
const float k_arenaWidth = static_cast<float>( k_windowWidth );
const float k_arenaHeight = static_cast<float>( k_windowHeight );
// End of window values
//------------------------------------------------------------------------------------------------
// Main Menu Config
const float k_menuElementsYStart = static_cast<float>( k_windowHeight / 3 );
const float k_menuElementsYIncrement = 60.0f;
const char k_menuElements[][12] = { "Start Game", "High Scores", "Options", "Credits", "Exit Game" };
const float k_menuFontOutlineThickness = 1.0f;
const int k_menuElementsSize = 32;
const char k_optionsFxVolumeString[] = { "Effects Volume: " };
const char k_optionsMusicVolumeString[] = { "Music Volume: " };
const char k_backString[] = { "Back" };
const int k_optionsElementsNum = 3;
const float k_volumeIncrement = 5.0f;
const float k_volumeMax = 100.0f;

const int k_menuElementsNum = 5;
// End of menu config
//------------------------------------------------------------------------------------------------
// How To Play Screen Config

// End of how to play screen config
//------------------------------------------------------------------------------------------------
// Credits Config
const float k_creditsScrollSpeed = 75.0f;
const char k_creditsDevString[] = { "Developed and designed by" };
const char k_creditsNameString[] = { "Dean Pearce" };
const char k_creditsMusicString[] = { "Copyright free music" };
const char k_creditsMenuMusic[] = { "Jeremy Blake - Powerup!" };
const char k_creditsGameMusic[] = { "Joshua McLean - Mountain Trials" };
const char k_creditsFxString[] = { "Sound Effects" };
const char k_creditsZapsplatString[] = { "www.zapsplat.com" };
const char k_creditsFontString[] = { "Font" };
const char k_creditsFreeFontString[] = { "www.1001fonts.com" };
const float k_creditsGap = 100.0f;
const float k_creditsSubGap = 55.0f;
const int k_creditsElementsNum = 9;
const int k_creditsHeaderSize = 38;
const int k_creditsSubHeaderSize = 22;
// End of credits config
//------------------------------------------------------------------------------------------------
// Pause Menu Config
const float k_pauseElementsYStart = static_cast< float >( k_windowHeight / 3 );
const float k_pauseElementsYIncrement = 60.0f;
const char k_pauseElements[][15] = { "Resume", "Restart", "Options", "Return to Menu", "Exit Game"};
const float k_pauseFontOutlineThickness = 1.0f;
const int k_pauseMenuElementsSize = 32;
const int k_pauseElementsNum = 5;
// End of pause menu config
//------------------------------------------------------------------------------------------------
// Game Over/Level Complete Menu Config
const float k_endGameElementsYStart = static_cast< float >( k_windowHeight / 2 );
const float k_endGameElementsYIncrement = 60.0f;
const int k_endElementsSize = 32;
const float k_endGameMenuGap = 100.0f;
const char k_endGameElements[][15] = { "Play Again", "Return to Menu", "Exit Game" };
const float k_endGameFontOutlineThickness = 1.0f;
const char k_endGameVictoryString[] = { "Victory!" };
const char k_endGameFailString[] = { "Defeated!" };
const char k_endGameYouScoredString[] = { "Your Score: " };

const int k_endGameElementsNum = 3;
// End of game over/level complete menu config
//------------------------------------------------------------------------------------------------
// Animation Config
const float k_animDefaultScale = 1.0f;
const float k_animScaleSpeed = 0.2f;
const float k_animScaleOffset = 0.05f;
const float k_bgSpeed = 100.0f;
//End of animation config
//------------------------------------------------------------------------------------------------
// Player Config
const float k_playerScaleX = 0.4f;
const float k_playerScaleY = 0.4f;

const float k_playerMoveSpeed = 250.0f;

const float k_playerTiltAngle = 5.0f;

const float k_playerReloadDelay = 0.75f;
const int k_playerMaxFiredBullets = 6;

const float k_playerInvulnTime = 3.0f;
const float k_playerFlashAnimTime = 0.1f;

const int k_playerHealth = 3;
const int k_playerLives = 3;

const sf::Color k_playerDefaultColor = sf::Color(255, 255, 255, 255);
const sf::Color k_playerDamagedColor = sf::Color(255, 140, 140, 125);
// End of player config
//------------------------------------------------------------------------------------------------
// Enemy Config
const float k_defaultEnemyScale = 0.3f;

// Movement values
const float k_gapBetweenEnemies = 15.0f;
const float k_enemyXSpeed = 100.0f;
const float k_enemyYSpeed = 35.0f;
const float k_enemyYMoveDistance = 50.0f;
const float k_enemyFormationSpeed = 50.0f;

// Formation values
const float k_formationReturnSpeed = 0.5f;
const float k_formationXOffset = 150.0f;
const float k_formationYOffset = 50.0f;
const float k_formationYMoveTime = 5.0f;

// Firing values
const float k_enemyMaxFireDelay = 1.8f;
const float k_enemyMinFireDelay = 0.1f;
const int k_enemyMaxFiredBullets = 5;
const int k_enemyMaxReadyToFire = 5;
const float k_enemyRangeOffset = 25.0f;
const float k_enemyDelayBeforeAutoFire = 1.5f;
const float k_enemyReloadDelay = 3.0f;
const float k_enemyDefaultFireDelay = 5.0f;

// Diving values
const float k_enemyDiveSpeed = 0.4f;
const float k_enemyLerpXDefault = 0.5f;
const float k_enemyMaxDiveDelay = 10.0f;
const float k_enemyMinDiveDelay = 4.0f;
const int k_enemyMaxDiving = 2;
const float k_enemyToPlayerYDive = k_arenaHeight / 2;
const float k_enemyDiveWaveSpeed = 1.0f;
const float k_enemyDiveXOffset = 100.0f;
const float k_enemyDiveYOffset = 20.0f;

const int k_enemyScoreValue = 25;

// Initialisation values
const int k_totalEnemyRows = 4;
const int k_maxEnemiesPerRow = 8;
const float k_enemyYStart = 50.0f;
const float k_enemyRowGap = 75.0f;
const float k_enemySpawnSpeed = 10.0f;
const float k_enemySpawnLookAtYOffset = 175.0f;
const float k_enemyInterpolateOffset = 0.15f;
const sf::Vector2f k_leftSpawn = sf::Vector2f( 0, k_windowHeight / 2 );
const sf::Vector2f k_rightSpawn = sf::Vector2f( k_windowWidth, k_windowHeight / 2 );
// End of enemy config
//------------------------------------------------------------------------------------------------
// Wave Config
const int k_waveTotalEnemies[] = { 16, 24, 32 };

// Working out the total waves based on the array above
// Pointer arithmetic from https://www.educative.io/edpresso/how-to-find-the-length-of-an-array-in-cpp
const int k_totalWaves = *( &k_waveTotalEnemies + 1 ) - k_waveTotalEnemies;
const float k_waveStartDelay = 2.5f;
// End of wave config
//------------------------------------------------------------------------------------------------
// Bullet Config
const float k_defaultBulletSpeed = 500.0f;
const float k_defaultBulletScale = 0.5f;
const int k_defaultBulletArraySize = 20;
const int k_playerBulletArraySize = 20;
const int k_enemyBulletArraySize = 20;
const float k_diagonalShotAngle = 45.0f;
// End of bullet config
//------------------------------------------------------------------------------------------------
// Barrier Config
// Odd numbers work best for barrier num
const int k_barrierNum = 3;
const float k_barrierHeight = static_cast<float>( k_windowHeight ) - 200.0f;
const int k_barrierHealth = 3;
const int k_barrierSpriteColumns = 1;
const float k_barrierScale = 0.6f;
const float k_gapBetweenBarriers = 100.0f;
// End of barrier config
//------------------------------------------------------------------------------------------------
// Sound Config
const float k_fxDefaultVolume = 10.0f;
const float k_musicDefaultVolume = 5.0f;
// End of sound config
//------------------------------------------------------------------------------------------------
// Hud Config
const float k_healthAmmoHudScale = 0.5f;
const float k_livesDisplayedScale = 0.3f;
const char k_scoreString[] = { "Score " };
const int k_scoreStringSize = 20;
const int k_youScoredStringSize = 36;
const int k_victoryFailStringSize = 50;
const float k_scoreStringGapFromBorder = 10.0f;
const sf::Color k_healthAmmoDefaultColor = sf::Color( 255, 255, 255, 255 );
const sf::Color k_healthAmmoDepletedColor = sf::Color( 255, 255, 255, 120 );
// End of hud config
//------------------------------------------------------------------------------------------------
// HiScore Config
const int k_scoreInitialsLength = 3;
const int k_savedHighScoresNum = 10;
const char k_defaultInitials[] = "AAA";
const float k_highScoreYPosStart = 50.0f;
const int k_highScoreStringSize = 50;
const int k_scoreboardFontSize = 32;
const float k_scoreboardXSpacing = 100.0f;
const float k_scoreboardYSpacing = 50.0f;
const float k_scoreboardYSpaceFromTitle = 100.0f;
const char k_highScoreString[] = { "High Scores" };
const char k_defaultScoreString[] = { "0000" };

const char k_continueString[] = { "Press 'Space' to Continue" };
const int k_continueStringSize = 28;
// End of HiScore config
//------------------------------------------------------------------------------------------------
// Initials Input Config
const char k_enterInitialsString[] = { "Enter your initials" };
const int k_enterInitialsStringSize = 32;
const char k_newHiScoreString[] = { "New High Score!" };
const int k_newHiScoreStringSize = 50;
const int k_initialsInputSize = 38;
const float k_initialsInputGap = 125.0f;
const int k_initialsScreenScoreSize = 44;
const float k_initialsScreenScoreYPos = k_windowHeight / 3;

const float k_enterInitialsYPos = ( k_windowHeight / 3 ) * 2;
const float k_newHiScoreYPos = 50.0f;

const char k_alphabetUpper[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
// End of input config
//------------------------------------------------------------------------------------------------

#endif // End of '#ifndef SETTINGS_H'
# Duel Game

## GENERAL PRINCIPLES
- Field size: 5x21
- Coordinates range from 0 to 20 (0-9 for the player, 11-20 for the bot)
- At the beginning of the game, the player selects 3 characters out of 6, and the bot receives the remaining 3.
- Characters start at coordinates 0, 2, and 4 from their respective ends of the field, depending on the selection.
- Players take turns for each character, starting from the leftmost character.
- Each turn, a player can choose one action:
  1) Move
  2) Apply an effect
  3) Shoot
  4) Use an ability
- Various events are resolved using a random dice roll with a spread (1, x). X is inversely proportional to the event probability. Successful events occur on rolls of 1 and 2.
- Before each character's turn, abilities are checked.
- After each character's turn, shots are checked for hits, health is updated, and the map is refreshed.
- Control is based on coordinates and command numbers.
- Victory is achieved by eliminating the entire opposing team.

## CHARACTERS
- **Piper (1)**
  - Shoots diagonally up to 6 squares vertically/horizontally or up to 7 squares diagonally (Hit chance x = 5).
  - Moves 1-3 squares vertically/horizontally.
- **Edgar (2)**
  - Shoots diagonally up to 3 squares or 1 square diagonally (Hit chance 1).
  - Moves 1-3 squares diagonally.
- **Bonnie (3)**
  - Shoots diagonally up to 7 squares vertically/horizontally or up to 6 squares diagonally (Hit chance x = 5).
  - Moves 1 square in any direction.
- **Frank (4)**
- **Poco (5)**
- **Grom (6)**
  - Shoots diagonally in a cross pattern of length 3 or at any square within a 5x5 area (Hit chance x = 4).
  - Moves 1-2 squares vertically/horizontally.

## EFFECTS
- **Health Restoration** (2, 5)
- **Invisibility**: Disappears from the map for 4 turns (3, 6)
- **Power Boost**: Lasts for one turn (1, 4)

## ABILITIES
- **(1)** ...
- **(2)** ...
- **(3)** ...
- **(4)** ...
- **(5)** ...
- **(6)** ...


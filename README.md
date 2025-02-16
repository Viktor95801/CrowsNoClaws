# Crows No Claws

<img src="assets\CrowsNoClawsLogo.png" width="300" height="300">

Crows No Claws is a simple chess engine that is being developed by a complete begginer at the topic. The name was choosen with the intention to represent how limited the engine is (after all, what would a crow with no claws be able to do?).

## How to compile

1. run the following command (assuming root directory):
```bash
gcc -Wall -Werror -o build/CrowsNoClaws -Iincludes crowsnoclaws.c src/board.c src/move_generator.c src/constant.c src/magic/magic.c -O3
```
2. Download from the releases option (not yet released).

### TODO

- [x] Simple board representation
    - [x] Initialize board
    - [x] Print board
- [ ] Add move generator
    - [ ] Black Magic
    - [ ] Legal Moves
    - [ ] Castling
    - [ ] En Passant
    - [ ] Promotion
- [ ] Improve board
    - [ ] Higher level representation for 32bit systems compatibility 
    - [ ] Optimize code
- [ ] Implement eval
    - [ ] Centipawn eval - varying knight and bishop value
    - [ ] Normal eval
    - [ ] NNUE eval
- [ ] Move Ordering
- [ ] Implement search
    - [ ] Alpha-Beta
    - [ ] Monte Carlo
- [ ] Basic UCI
- [ ] Implement UI
    - [ ] CLI
    - [ ] GUI
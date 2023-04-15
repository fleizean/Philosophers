# Philosophers

This project is aimed at multi-threaded/multi-processed programming using mutexes and semaphores. We need to write a program that simulates the Famous Philosophers problem.

# RULES


- Several philosophers are sitting at a round table and doing one of three things:
- eating, thinking, or sleeping.
- They do not think or sleep while eating, or eat while sleeping. Or of course, they do not eat or sleep - while thinking.
- The philosophers are sitting at a circular table with a large spaghetti bowl in the middle.
- There are some forks on the table.
- Because it is difficult to serve and eat spaghetti with one fork, the philosopher
- must eat with two forks, one for each hand.
- If the given parameters are correct, philosophers should never die of hunger.
- Each philosopher must eat.
- Philosophers do not talk to each other.
- Philosophers cannot know when another philosopher dies.
- When a philosopher finishes eating, they fall asleep.
- When a philosopher finishes sleeping, they start thinking.
- If a philosopher dies, the simulation ends.

# Dining Philosophers Problem

This repository contains a C implementation of the **Dining Philosophers** problem, demonstrating concurrency and synchronization using threads and mutexes.

## Features

- Multi-threaded implementation using `pthread`.
- Thread-safe synchronization with mutexes.
- Customizable parameters via command-line arguments.
- Accurate logging of state changes.

## Usage

### Compilation

```bash
make
```

### Running

```bash
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<meals_per_philosopher>]
```

Example:

```bash
./philosophers 5 800 200 200
```

### Simulation States

Philosophers alternate between:

- **Thinking**
- **Eating** (requires both forks)
- **Sleeping**
- **Died** (if they exceed `time_to_die` without eating)

## Constraints

- No global variables.
- Allowed functions: `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_*`.
- Logs must be synchronized and include timestamps in milliseconds.

## Acknowledgments

Project from the **42 School** curriculum showcasing advanced multi-threading concepts.


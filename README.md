# cfsd19-autonomous-system-usecases
The usecases for CFSD19
-----------------------------

This repository contains a directory for each *Use Case* for the vehicle. During a *Use Case* we simply execute some behaviour, e.g. testing the cone detection software, or competing in the Acceleration Event.

*[TO-DO]*: Provide example of a Use Case and the services it utilizes for this README.

From the dashboard on the CFSD car, you can select a Autonomous Mission. Selecting a mission simply means that we point to the corresponding Use Case script on the Lynx (main) computer.
When our system is in the AS-Ready state (see rules), and we send the Go-signal, we run the aforementioned script. This script places us in the Use Case directory on the Lynx computer, and runs the Docker compose. All images are cached locally on Lynx. (Docker Compose will not have to fetch images from Docker Hub)

Each Use Case directory simply contains the following:
- *docker-compose.yml*: The docker-compose file that starts the containers that are needed for the Use Case.
- *.env*: A list of variable values that are substituted into docker-compose.yml


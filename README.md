# swig-exercise
Just an exercise in using SWIG and exploring it's capabilities and integration

## Setup
My current development environment uses MacOS Catalina. In order to create a generic set of setup instructions, I've opted to use a Docker container running off of a vanilla Ubuntu 18.04 image. What follows will be the steps taken to create the proper development environment for using SWIG to target Java and Javascript as the desired languages to support the source shared library.

### Step 1 - Docker Container Setup
**Note**
If you are already using an Ubuntu 18.04 Docker container, or are have bootstrapped an Ubuntu 18.04 OS, then please skip this step and proceed onto the next.

Download and install the desktop version of Docker for your current OS:

##### Mac
Download the installer from the Docker website [here](https://www.docker.com/products/docker-desktop).

Once it's been installed, it should automatically start running in a background process, which is typically accessed via the toolbar/taskbar icon.

##### Ubuntu
Update your existing list of packages:
```
$ sudo apt update
```

Install dependency packages:
```
$ sudo apt install apt-transport-https ca-certificates curl software-properties-common
```

Add the Docker repository GPG key to your system:
```
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
```

Add the Docker repository to the APT sources:
```
$ sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable"
```

Update your package database again, this time having the Docker repository packages included:
```
$ sudo apt update
```

Install Docker:
```
$ sudo apt install docker-ce
```

Check that Docker is running:
```
$ sudo systemctl status docker
```

#### Mount the Docker Image and Startup a New Container
Obtain a copy of the Ubuntu core 18.04 Dockerfile [here](https://github.com/tianon/docker-brew-ubuntu-core/blob/14faa76f80e543f7507828430ff50b4a58466ffd/bionic/Dockerfile).

Download a copy of the Ubuntu 18.04 Docker image archive from [here](https://partner-images.canonical.com/core/bionic/current/) and place it in the same location as the downloaded Dockerfile.

In a new terminal window, navigate to the location of the downloaded Dockerfile to mount the Ubuntu Docker image and start up a new container that will host our development environment:
```
$ docker build --file Dockerfile --tag ubuntu-18.04 .
```

To obtain the *container ID* of the newly created container:
```
$ docker container ls -a  # make note of the container 
```

Start up the new container:
```
$ docker run --interactive --tty ubuntu-18.04:latest
```

To attach your shell session to a created and running container:
```
$ docker container start --attach --interactive <CONTAINER_ID>
```

### Step 2 - Install the Development Prerequisites
**Note**
Your user will be logged in as *root* when attached to the Docker container. If you are not performing the subsequent steps within a Docker container, then the command may require `sudo` execution, and some of the installation and reference paths may differ (e.g. `/usr/bin` vs `/usr/local/bin`).

#### Update the APT repository
```
$ apt update
```

#### Install Git
```
$ apt install git
```

#### Install the Build Toolchain
```
$ apt install build-essential
```

#### Install Wget
```
$ apt install wget
```

#### Install SWIG and its Dependencies
Obtain the SWIG source archive:
```
$ wget -O swig-4.0.1.tar.gz "https://downloads.sourceforge.net/project/swig/swig/swig-4.0.1/swig-4.0.1.tar.gz?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fswig%2Ffiles%2Fswig%2Fswig-4.0.1%2Fswig-4.0.1.tar.gz%2Fdownload&ts=1576954647
https://sourceforge.net/projects/swig/files/swig/swig-4.0.1/swig-4.0.1.tar.gz/download"
```

Extract the SWIG sources:
```
$ tar -xzvf swig-4.0.1.tar.gz
$ cd swig-4.0.1
```

Download and Install the Perl Compatible Regular Expressions (PCRE) Library:
```
$ wget "https://ftp.pcre.org/pub/pcre/pcre-8.43.tar.gz"
$ Tools/pcre-build.sh
```

Install SWIG:
```
$ ./configure
$ make
$ make install
```

### Step 3 - Clone this Repository and Install its Dependencies

#### Clone the Project
```
$ git clone https://github.com/oo-swoop-oo/swig-exercise.git
$ cd swig-exercise
```

#### Install pkg-config
```
$ apt install pkg-config
```

#### Install the libcurl Development Package
```
$ apt install libcurl4-gnutls-dev
```

#### Install the NodeJS Development Package and Dependencies
```
$ apt install libssl1.0-dev
$ apt install nodejs-dev
```

#### Install Node Version Manager (NVM) and NodeJS 10.18.0 LTS
```
$ curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.34.0/install.sh > install.sh
$ bash ./install.sh
$ source ~/.profile
$ nvm install 10.18.0
```

#### Install node-gyp via NPM
```
$ npm install -g node-gyp
```

#### Install the OS Default Java Developer Kit (JDK)
```
$ apt install default-jdk
```

## Building the SWIG Shared Libraries
Under the `script/` directory, you'll find development scripts organized by target language. For each target language, there are two scripts used to aid in building and testing of the generated Javascript shared libraries:

  * `build.sh` - builds the shared libraries
  * `clean.sh` - cleans the artifacts generated by the `build.sh` script

The build steps and compilation options can be observed by viewing the contents of the `build.sh` script. In either case, both scripts are run without any arguments.

## Testing the SWIG Shared Libraries

Under the `test/` directory, you'll find test harness projects organized by target language. The contents of each test project vary depending on the target language.

### Javascript
This test project is a NodeJS application and can be invoked by running `node index.js` within the test project root.

### Java
This test project is a Java application. Under the `test/java/script/` directory, you'll find three development scripts:

  * `build.sh` - the bytecode for each user Java class of the project
  * `run.sh` - runs the Java application based off of the artifacts generated from the `build.sh` script and the SWIG generated shared libraries
  * `clean.sh` - cleans the artifacts generated by the `build.sh` script

## Examples
Examples of using SWIG from the SWIG documentation can be found under the `example` folder.

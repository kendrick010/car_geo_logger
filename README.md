<!------------------------------------------ TITLE BLOCK --------------------------------------------------------------->
<h1 align="center"> Geo Motors </h1>

<p align="center">
    A Geolocation Logger for Cars
    <br /> <br />
    <a href="https://github.com/github_username/repo_name"> View Demo </a>
    ·
    <a href="https://github.com/github_username/repo_name/issues"> Report Bug </a>
    ·
    <a href="https://github.com/github_username/repo_name/issues"> Request Feature </a>
</p>


<!------------------------------------------ TABLE OF CONTENTS ---------------------------------------------------------->
<details open="open">
  <summary><h2 style="display: inline-block"> Table of Contents </h2></summary>
  <ol>
    <li>
      <a href="#about-the-project"> About The Project </a>
      <ul>
        <li><a href="#technologies"> Technologies </a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started"> Getting Started </a>
      <ul>
        <li><a href="#prerequisites"> Prerequisites </a></li>
        <li><a href="#installation"> Installation </a></li>
      </ul>
    </li>
    <li><a href="#usage"> Usage </a></li>
    <li><a href="#high-level-architecture"> High Level Architecture </a></li>
    <li><a href="#contributing"> Contributing </a></li>
  </ol>
</details>


<!------------------------------------------ ABOUT THE PROJECT ---------------------------------------------------------->
## About The Project
Apple has this feature called Screen Time that pings users a daily/weekly summary on how much time you spend on
certain apps, and I thought it would be neat to create a similar app that gives you a report on car drives. At the bare
minimum, I envisioned the app to graphically report miles, speeds, or routes for car trips throughout the week. Although
there are countless available apps that already do this, I wanted to challenge myself by designing my own solution. I
am inclined to the hardware side of engineering, so I decided to create an IoT device that pairs with the app.

### Technologies
* [ESP32](https://www.espressif.com/en/products/socs/esp32)
* [PlatformIO](https://platformio.org/)
* [Altium Designer](https://www.altium.com/)
* [SwiftUI - XCode](https://developer.apple.com/xcode/swiftui/)


<!------------------------------------------ GETTING STARTED ---------------------------------------------------------->
## Getting Started
To get a local copy up and running follow these steps.

### Prerequisites
Obtain and assemble the PCB. Download the latest gerber zip file version and request a quote from JLCPCB. The PCB was 
designed with JLCPCB's design rules and stackups, so I do not recommend quoting from another manufacturer. The default PCB
specification is sufficient enough when ordering. When assembling and soldering the PCB, consult to the 
[BOM and Build Guide](docs/README.md).

Install PlatformIO via Visual Studio Code. PlatformIO is a neat integration for embedded development, and we will be using
it to program/upload code to our ESP32. PlatformIO offers convenient features, such as port detection, larger boards selection, 
pre-loaded libraries, and all other features offered in any code editor.

System Requirements:
* Visual Studio Code installed
* Python 3.x or the latest version

### Installation


<!------------------------------------------ USAGE EXAMPLES -------------------------------------------------------------->
## Usage


<!------------------------------------------ HIGH LEVEL ARCHITECTURE ----------------------------------------------------->
## High Level Architecture


<!------------------------------------------ CONTRIBUTING ---------------------------------------------------------------->
## Contributing


<!------------------------------------------ CONTACT --------------------------------------------------------------------->
## Contact

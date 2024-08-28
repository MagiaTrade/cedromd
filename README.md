# cedromd Library

`cedromd` is a C++ library designed to implement all endpoints of the socket API for market data provided by Cedro, except for the news endpoint at the moment. It provides robust support for connecting to and interacting with Cedro's market data services.

> **⚠️ Important:** There is an `API_socket.pdf` file in the root of the project that documents the version of the API for which this project was built. Any updates to the API will be reflected with the corresponding documentation attached in this manner.


## Features
Comprehensive Market Data Endpoints: The library implements multiple market data endpoints, including:

- **SQT**: Subscribe to real-time quotes as well as the snapshot.
- **GPN**: Get player names, providing market participant information.
- **GQT**: Subscribe to real-time quote trades, capturing trade-level data.
- **SAB**: Subscribe to aggregated book data, offering a view of market depth.
- **BQT**: Subscribe to book quotes, detailing order book movements.
- **VAP**: Snapshot volume at price, aggregating volume traded at specific price levels over time.
- **Error Handling**: Includes comprehensive error management and callback mechanisms to handle connection issues and data errors gracefully.

Dual Data Management Implementations:

- **CMDBaseManager**: Provides a callback system for raw data `(const char*, size_t lenght)` from the API endpoints, optimized for high performance and low-latency applications.
- **CMDProcessedManager**: Delivers parsed data models through callbacks, offering ready-to-use structured data for each endpoint.


## Installation

> **⚠️ Warning:** This project has only been tested on macOS.

### Required Packages

To use `cedromd`, you need to install the following packages:

- [Boost (minimum version 1.83.0)](http://boost.org)
- [OpenSSL (version 1.1)](https://www.openssl.org)

Additionally, `cedromd` depends on the `beastboys` library as a submodule. The dependencies above are actually for `beastboys`.

#### macOS Installation

Install the required packages using Homebrew:

```sh
brew install boost@1.83.0
brew install openssl@1.1
```

#### Linux Installation

On Linux, you can install Boost and OpenSSL using your package manager. For example, on Ubuntu:

```sh
sudo apt-get update
sudo apt-get install -y libboost1.83-dev libssl1.1-dev
```

If Boost 1.83.0 is not available in your distribution, you may need to download and build it manually from the [Boost website](https://www.boost.org/users/download/).

#### Windows Installation

On Windows, you can install Boost and OpenSSL using a package manager like vcpkg:

```sh
vcpkg install boost@1.83.0
vcpkg install openssl@1.1
```

Make sure to integrate vcpkg with your Visual Studio environment:

```sh
vcpkg integrate install
```

The CMake configuration for the project will resolve any additional dependencies automatically.

## Authentication
To authenticate with Cedro servers using your account, you need to provide your credentials in a local environment file. This project uses a file named env.local.cmake for this purpose.

### Steps to Set Up Authentication
* Create an Authentication File: Copy the provided **env.template.cmake** file, which is located in the cmake directory at the root of the project, and rename it to **env.local.cmake**.

* Edit Your Credentials: Open **env.local.cmake** and fill in your Cedro credentials as shown below:
```cmake
set(CEDRO_USERNAME "your_username_here")   # Replace with your Cedro username
set(CEDRO_PASSWORD "your_password_here")   # Replace with your Cedro password
set(CEDRO_SOFTKEY "your_softkey_here")     # Replace with your Cedro softkey, or leave empty if not applicable
```
* Place the File Correctly: Ensure that ***env.local.cmake** is also located in the cmake directory at the root of the project, just like the template file.

* Save the File: Make sure to save your changes to **env.local.cmake**.

## Documentation and Tests

The test files included in this repository serve as **living documentation**. They provide concrete examples of how to use the various features of the `cedromd` library, including subscribing to market data streams, handling snapshots, managing different types of market data, and processing data updates. By examining and running these tests, users can gain a better understanding of the library's functionality and intended use cases.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

## Authors

* **Tato Levicz** - [@tatolevicz](https://github.com/tatolevicz)

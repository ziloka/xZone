FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-22.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.22.2"

# Optionally install the cmake for vcpkg
# COPY ./reinstall-cmake.sh /tmp/

# RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
#         chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
#     fi \
#     && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends libgtest-dev libopencv-dev libboost-dev

# fastdds-tools

# Install Fast DDS
RUN wget https://www.eprosima.com/index.php/component/ars/repository/eprosima-fast-dds/eprosima-fast-dds-2-9-1/eprosima_fast-dds-v2-9-1-linux-tgz?format=raw \
    && tar xzvf eProsima_Fast-DDS-v2.9.1-Linux.tgz \
    && cd tar xzvf eProsima_Fast-DDS-v2.9.1-Linux \
    && chmod +x install.sh \
    && sudo ./install.sh

# Fast DDS root is located at /usr/local/bin/fastddsgen

# Opencv files are located at /usr/include

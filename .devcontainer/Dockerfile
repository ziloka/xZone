FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-20.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.22.2"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        wget build-essential googletest \
        libopencv-dev libboost-dev libboost-all-dev \
        libv4l-dev \
    && wget -O eProsima_Fast-DDS-v2.12.1-Linux.tgz https://www.eprosima.com/index.php/component/ars/repository/eprosima-fast-dds/eprosima-fast-dds-2-12-1/eprosima_fast-dds-v2-12-1-linux-tgz?format=raw \
    && tar xzf eProsima_Fast-DDS-v2.12.1-Linux.tgz \
    && sudo ./install.sh \
    && echo "include /usr/local/lib" >> /etc/ld.so.conf \
    && ldconfig

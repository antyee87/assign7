FROM ghcr.io/linuxserver/baseimage-kasmvnc:ubuntujammy-version-d70fa76b

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ffmpeg \
    qt6-*dev \
    libopengl-dev \
    libgl-dev \
    libglu1-mesa-dev \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    && apt-get clean

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make

CMD ["./build/assign7"]


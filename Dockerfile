FROM gcc:14
WORKDIR /app
RUN apt-get update && apt-get install -y cmake

COPY . .

CMD sh -c "cmake -S . -B build && cmake --build build && ./build/test_poly"


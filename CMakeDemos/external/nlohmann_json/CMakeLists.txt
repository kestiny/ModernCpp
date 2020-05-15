include(FetchContent)

FetchContent_Declare(
   nlohmann_json
   URL  ftp://gjg-fwq/share/nlohmann_json_v3.7.0.zip
   URL_HASH SHA512=d3bc3c4e34d36ab0899f4ad5c1ed97fedc337e50bb11f15708d5e01f29229e684729f1ea289d6a0a3c46e3167dea9015eafec1dbd650ce718ae4dac0dd0a9d6f
   DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/../external/downloads/nlohmann_json
)

FetchContent_MakeAvailable(nlohmann_json)
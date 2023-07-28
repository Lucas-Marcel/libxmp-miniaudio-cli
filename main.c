#define MINIAUDIO_IMPLEMENTATION

#include "miniaudio.h"
#include "libxmp-lite/xmp.h"

// This function is called by miniaudio to fill the audio buffer with data
void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    xmp_context ctx = (xmp_context)pDevice->pUserData; // Get the libxmp context from the device user data
    if (ctx == NULL) {
        return;
    }

    xmp_play_buffer(ctx, pOutput, frameCount * 4, 0); // Fill the audio buffer with data from the libxmp player
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]); // Print usage information if no filename is provided
        return 1;
    }

    // Load the module file using libxmp
    xmp_context ctx = xmp_create_context(); // Create a new libxmp context
    if (xmp_load_module(ctx, argv[1]) != 0) { // Load the module file specified by the first command-line argument
        printf("Error loading module file.\n"); // Print an error message if the module file could not be loaded
        return 1;
    }
    xmp_start_player(ctx, 44100, 0); // Start the libxmp player with a sample rate of 44100 Hz
    
    xmp_set_player(ctx, XMP_PLAYER_VOLUME, 50); // Sets master volume to 50. Range goes from 0 to 100
    
   
    // Set up the miniaudio playback device
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback); // Initialize a device config for a playback device
    deviceConfig.playback.format = ma_format_s16; // Set the playback format to signed 16-bit integers
    deviceConfig.playback.channels = 2; // Set the number of playback channels to 2 (stereo)
    deviceConfig.sampleRate = 44100; // Set the sample rate to 44100 Hz
    deviceConfig.dataCallback = data_callback; // Set the data callback function to fill the audio buffer with data
    deviceConfig.pUserData = ctx; // Set the user data to the libxmp context so it can be accessed in the data callback

    ma_device device;
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) { // Initialize the playback device with the specified config
        printf("Error initializing playback device.\n"); // Print an error message if the device could not be initialized
        return 1;
    }

    // Start playback
    ma_device_start(&device); // Start playback on the device
    printf("Audio is playing now. Press Enter to stop playback...\n"); // Print a message indicating that audio is playing
    getchar(); // Wait for user input to stop playback

    // Clean up
    ma_device_uninit(&device); // Uninitialize the playback device
    xmp_end_player(ctx); // Stop the libxmp player
    xmp_release_module(ctx); // Release the loaded module from memory
    xmp_free_context(ctx); // Free the libxmp context

    return 0;
}

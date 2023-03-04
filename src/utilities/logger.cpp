#include "logger.hpp"

#include <ctime>

namespace Farscape_Logger
{
    Logger::Logger()
    {
    }

    Logger::~Logger()
    {
        free_file();
    }

    void Logger::enable_file_out()
    {
        std::time_t current_time = std::time(0);
        std::tm *timestamp = std::localtime(&current_time);
        char fileNameBuffer[80];
        strftime(fileNameBuffer, 80, "%d_%m_%Y_%H-%M-%S_log.txt", timestamp);
        enable_file_out(fileNameBuffer);
    }

    void Logger::enable_file_out(char const *fileName)
    {
        ensure_logs_directory_exists();
        char buffer[120];
        *buffer = '\0';
        strcat(buffer, LOGS_FOLDER_PATH);
        strcat(buffer, fileName);
        if (file)
            fclose(file);
        file = fopen(filepath, "w");
        if (!file)
            printf("failed to open file at %s", filepath);
    }

    void Logger::ensure_logs_directory_exists()
    {
#ifdef _WIN32
        DWORD dwAttribute = GetFileAttributes(LOGS_FOLDER_PATH);
        if (dwAttribute == INVALID_FILE_ATTRIBUTES)
        {
            CreateDirectory(LOGS_FOLDER_PATH, NULL);
            dwAttribute = GetFileAttributes(LOGS_FOLDER_PATH);
            if (dwAttribute == INVALID_FILE_ATTRIBUTES)
            {
                fprintf(stderr, "Can not create logs directory!\n");
                exit(70);
            }
        }
        else if (!(dwAttribute & FILE_ATTRIBUTE_DIRECTORY))
        {
            fprintf(stderr, "Logs is not a directory");
            exit(70);
        }
#endif
#ifdef __linux__
        DIR *resultsDirectory = opendir(LOGS_FOLDER_PATH);
        if (resultsDirectory)
            closedir(resultsDirectory);
        else if (ENOENT == errno)
        {
            // If the directory does not exists we need to create it
            mkdir(RESULTS_BASE_PATH, 0700);
            resultsDirectory = opendir(LOGS_FOLDER_PATH);
            if (resultsDirectory)
                closedir(resultsDirectory);
            else
            {
                fprintf(stderr, "Can not create results directory!\n");
                exit(70);
            }
        }
        else
        {
            fprintf(stderr, "Can not access results directory!\n");
            exit(EXIT_CODE_SYSTEM_ERROR);
        }
#endif
    }

    void Logger::free_file()
    {
        if (file)
        {
            fclose(file);
            file = 0;
        }
    }
}
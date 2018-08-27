
// Compile and link like this:
// $ g++ aria2_downloader.cpp -laria2 -o aget
#include <iostream>
#include <chrono>
#include <utility>
#include <fstream>
#include <vector>
#include <string>

#include <string.h>

#include <sys/stat.h>
int exist(const char *name)
{
  struct stat buffer;
  return (stat(name, &buffer) == 0);
}

#if defined(__CYGWIN__) || defined(__DJGPP__) || defined(__MINGW32__)
#define IS_PATH_SEPARATOR(c) (((c) == '/') || ((c) == '\\'))
#else
#define IS_PATH_SEPARATOR(c) ((c) == '/')
#endif

/* per http://www.scit.wlv.ac.uk/cgi-bin/mansec?3C+basename */
char *basename(char *s)
{
  char *rv;

  if (!s || !*s)
    return ".";

  rv = s + strlen(s) - 1;

  do
  {
    if (IS_PATH_SEPARATOR(*rv))
      return rv + 1;
    --rv;
  } while (rv >= s);

  return s;
}

/* per http://www.scit.wlv.ac.uk/cgi-bin/mansec?3C+dirname */
char *dirname(char *path)
{
  char *p;

  if (path == NULL || *path == '\0')
    return ".";
  p = path + strlen(path) - 1;
  while (IS_PATH_SEPARATOR(*p))
  {
    if (p == path)
      return path;
    *p-- = '\0';
  }

  while (p >= path && !IS_PATH_SEPARATOR(*p))
    p--;

  if (p < path)
    return ".";

  if (p == path)
    return "/";

  *p = '\0';

  return path;
}

#include <aria2/aria2.h>

int downloadEventCallback(aria2::Session *session, aria2::DownloadEvent event,
                          aria2::A2Gid gid, void *userData)
{
  switch (event)
  {
  case aria2::EVENT_ON_DOWNLOAD_COMPLETE:
    std::cerr << "COMPLETE";
    break;
  case aria2::EVENT_ON_DOWNLOAD_ERROR:
    std::cerr << "ERROR";
    break;
  default:
    return 0;
  }
  std::cerr << " [" << aria2::gidToHex(gid) << "] ";
  aria2::DownloadHandle *dh = aria2::getDownloadHandle(session, gid);
  if (!dh)
    return 0;
  if (dh->getNumFiles() > 0)
  {
    aria2::FileData f = dh->getFile(1);
    // Path may be empty if the file name has not been determined yet.
    if (f.path.empty())
    {
      if (!f.uris.empty())
      {
        std::cerr << f.uris[0].uri;
      }
    }
    else
    {
      std::cerr << f.path;
    }
  }
  aria2::deleteDownloadHandle(dh);
  std::cerr << std::endl;
  return 0;
}

int Aria2Run(int argc, std::vector<std::string> argv)
{
  int rv;
  if (argc < 2)
  {
    std::cerr << "Usage: libaria2ex URI [URI...]\n"
              << "\n"
              << "  Download given URIs in parallel in the current directory."
              << std::endl;
    exit(EXIT_SUCCESS);
  }
  aria2::libraryInit();
  // session is actually singleton: 1 session per process
  aria2::Session *session;
  // Create default configuration. The libaria2 takes care of signal
  // handling.
  aria2::SessionConfig config;
  // Add event callback
  config.downloadEventCallback = downloadEventCallback;

  session = aria2::sessionNew(aria2::KeyVals(), config);
  // Add download item to session
  for (int i = 0; i < argc; ++i)
  {
    std::vector<std::string> uris = {argv[i]};
    std::string url = argv[i];
    std::string http = "http://";
    std::string https = "https://";
    size_t pos1 = url.find(http);
    if (pos1 != std::string::npos)
      url.replace(pos1, http.length(), "");
    size_t pos2 = url.find(http);
    if (pos2 != std::string::npos)
      url.replace(pos2, https.length(), "");

    if (exist(url.c_str()))
    {
      printf("%s has existed.\n", url.c_str());
      continue;
    }

    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    memcpy(buf, url.c_str(), url.length());
    char *filename = basename(buf);
    char *path = dirname(buf);
    // std::cout << filename << std::endl;
    // std::cout << path << std::endl;
    aria2::KeyVals options;

    options.push_back(std::make_pair("file-allocation", "none"));
    options.push_back(std::make_pair("out", filename));
    options.push_back(std::make_pair("dir", path));

    rv = aria2::addUri(session, nullptr, uris, options);
    if (rv < 0)
    {
      std::cerr << "Failed to add download " << uris[0] << std::endl;
    }
  }
  auto start = std::chrono::steady_clock::now();
  for (;;)
  {
    rv = aria2::run(session, aria2::RUN_DEFAULT);
    if (rv != 1)
    {
      break;
    }
    // the application can call aria2 API to add URI or query progress
    // here
    auto now = std::chrono::steady_clock::now();
    auto count =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
            .count();
    // Print progress information once per 500ms
    if (count >= 500)
    {
      start = now;
      aria2::GlobalStat gstat = aria2::getGlobalStat(session);
      std::cerr << "Overall #Active:" << gstat.numActive
                << " #waiting:" << gstat.numWaiting
                << " D:" << gstat.downloadSpeed / 1024 << "KiB/s"
                << " U:" << gstat.uploadSpeed / 1024 << "KiB/s " << std::endl;
      std::vector<aria2::A2Gid> gids = aria2::getActiveDownload(session);
      for (const auto &gid : gids)
      {
        aria2::DownloadHandle *dh = aria2::getDownloadHandle(session, gid);
        if (dh)
        {
          std::cerr << "    [" << aria2::gidToHex(gid) << "] "
                    << dh->getCompletedLength() << "/" << dh->getTotalLength()
                    << "(" << (dh->getTotalLength() > 0 ? (100 * dh->getCompletedLength() / dh->getTotalLength()) : 0)
                    << "%)"
                    << " D:" << dh->getDownloadSpeed() / 1024
                    << "KiB/s, U:" << dh->getUploadSpeed() / 1024 << "KiB/s"
                    << std::endl;
          aria2::deleteDownloadHandle(dh);
        }
      }
    }
  }
  rv = aria2::sessionFinal(session);
  aria2::libraryDeinit();
  return rv;
}

int main(int argc, char **argv)
{
  if (argc <= 1)
  {
    printf("%Usage:%s <urls_files>.\n", argv[0]);
    return 0;
  }
  std::vector<std::string> vec_str;
  std::ifstream ifs(argv[1]);
  std::string s;

  while (std::getline(ifs, s))
  {
    //s.pop_back();
    // std::cout << s << std::endl;
    vec_str.push_back(s);
  }
  std::cout << "load file finished." << std::endl;
  ifs.close();

  Aria2Run(vec_str.size(), vec_str);
  return 0;
}

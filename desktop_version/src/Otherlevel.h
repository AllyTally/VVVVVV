#ifndef OTHERLEVEL_H
#define OTHERLEVEL_H

#include <string>

class otherlevelclass
{
public:
    const short* loadlevel(int room_id);

    std::string roomname;

    int roomtileset;
};

#endif /* OTHERLEVEL_H */

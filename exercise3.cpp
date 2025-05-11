#include <iostream>
#include "queueCircArray.h"

struct Song
{
    enum Type{VIP = 1, Regular = 2, Low = 3} preference;
    int duration;
    std::string name;

    Song(){}

    Song(Type param_preference, int param_duration, std::string param_name)
    {
        preference = param_preference;
        duration = param_duration;
        name = param_name;
    }
};

void readCmd(std::string &cmd, int &preference_type, int &interval, std::string &name_song)
{   cmd = "";
    preference_type = 0;
    interval = 0;
    name_song = "";
    std::cin >> cmd;

    //for some commands we read additional parameters

    if (cmd == "ADD")
    {
        std::cin >> preference_type;
        std::cin >> interval;
        std::cin >> name_song;
    }

    else if (cmd == "SKIP")
    {
        std::cin >> interval;
    }

    else if (cmd == "REMOVE")
    {
        std::cin >> name_song;
    }

    /* for debugging purposes

    std::cout << "cmd: " << cmd << std::endl;
    std::cout << "preference_type: " << preference_type << std::endl;
    std::cout << "interval: " << interval << std::endl;
    std::cout << "name_song: " << name_song << std::endl << std::endl;
    */
}




class DJ {
    private:
        QueueCirc<Song> playlistVip;
        QueueCirc<Song> playlistRegular;
        QueueCirc<Song> playlistLow;
        QueueCirc<Song> history_of_played_songs;
        int current_song_time_left = 0; //how much time is left for the current song to finish playing (needed for skip function)

    public:
        // function to add a song to the desired playlist
        void add (Song song)
        {
            switch (song.preference)
            {
                case Song::Type::VIP:
                    playlistVip.enqueue(song);
                    break;
                case Song::Type::Regular:
                    playlistRegular.enqueue(song);
                    break;
                case Song::Type::Low:
                    playlistLow.enqueue(song);
                    break;
                default:
                    std::cout << "Invalid preference type." << std::endl;
                    break;
            }
        }

        // function to play a song (starting from the high-priority ones)
        void play (bool replay = false) // "replay" is a flag to indicate if the song is played for the first time or if it is replayed
        {

            if (!playlistVip.isEmpty())
            {
                Song song = playlistVip.dequeue();
                current_song_time_left = song.duration;
                if (history_of_played_songs.isEmpty() || song.name != history_of_played_songs.peekLast().name) 
                {
                    history_of_played_songs.enqueue(song);
                }
                
                if (!replay)
                {
                    std::cout << "Now playing: " << song.name << " (" << song.duration << "s)" << std::endl;
                }
            }
            else if (!playlistRegular.isEmpty())
            {
                Song song = playlistRegular.dequeue();
                current_song_time_left = song.duration;
                if (history_of_played_songs.isEmpty() || song.name != history_of_played_songs.peekLast().name)
                {
                    history_of_played_songs.enqueue(song);
                }

                if (!replay)
                {
                    std::cout << "Now playing: " << song.name << " (" << song.duration << "s)" << std::endl;
                }
            }

            else if (!playlistLow.isEmpty())
            {
                Song song = playlistLow.dequeue();
                current_song_time_left = song.duration;
                if (history_of_played_songs.isEmpty() || song.name != history_of_played_songs.peekLast().name)
                {
                    history_of_played_songs.enqueue(song);
                }

                if (!replay)
                {
                    std::cout << "Now playing: " << song.name << " (" << song.duration << "s)" << std::endl;
                }
            }
            else
            {
                std::cout << "There are no songs in the playlists." << std::endl;
            }
        }
        
        // function to print the history of played songs (in the order they were played)
        void history()
        {
            if (history_of_played_songs.isEmpty())
            {
                std::cout << "There are no songs in the history." << std::endl;
            }
            else
            {
                std::cout << "\nHistory:" << std::endl;
                for (int i = 1; i <= history_of_played_songs.getSize(); i++)
                {
                    Song song = history_of_played_songs.dequeue();
                    std::cout << i << ". " << song.name << std::endl;
                    history_of_played_songs.enqueue(song); 
                }
                std::cout << std::endl;
            }
        }

        // function to print all the songs in the preference playlists (in the order they were added, starting from the VIP-ones)
        void show()
        {
            std::cout << "Playlist:" << std::endl;
            std::cout << "Preference 1: ";
            if (!playlistVip.isEmpty())
            {
                Song lastVipSong = playlistVip.peekLast();

                for (int i = 0; i < playlistVip.getSize(); i++)
                {
                    Song song = playlistVip.dequeue();
                    if (song.name == lastVipSong.name)
                    {
                        std::cout << song.name << ".";
                    }
                    else
                    {
                        std::cout << song.name << ", ";
                    }
                    playlistVip.enqueue(song);
                }
            }
            
            std::cout << std::endl << "Preference 2: ";
            if (!playlistRegular.isEmpty())
            {
                Song lastRegularSong = playlistRegular.peekLast();
                for (int i = 0; i < playlistRegular.getSize(); i++)
                {
                    Song song = playlistRegular.dequeue();
                    if (song.name == lastRegularSong.name)
                    {
                        std::cout << song.name << ".";
                    }
                    else
                    {
                        std::cout << song.name << ", ";
                    }
                    playlistRegular.enqueue(song);
                }
            }
            
            std::cout << std::endl << "Preference 3: ";
            if (!playlistLow.isEmpty()){
                Song lastLowSong = playlistLow.peekLast();
                for (int i = 0; i < playlistLow.getSize(); i++)
                {
                    Song song = playlistLow.dequeue();
                    if (song.name == lastLowSong.name)
                    {
                        std::cout << song.name << ".";
                        std::cout << std::endl;
                    }
                    else
                    { 
                        std::cout << song.name << ", ";
                    }
                    playlistLow.enqueue(song);
                }
            }

        }

        // function to skip n seconds of the current song
        void skip(int n)
        {
            if (playlistVip.isEmpty() && playlistRegular.isEmpty() && playlistLow.isEmpty())
            {
                std::cout << "There are no songs in the playlists." << std::endl;
                return;
            }

            else if (current_song_time_left <= 0)
            {
                std::cout << "There is no song playing." << std::endl;
                return;
            }

            else 
            {
                current_song_time_left -= n;
                if (current_song_time_left > 0)
                {
                    std::cout << "Skipped " << n << "s. " << current_song_time_left << "s remaining." << std::endl;
                }
                else
                {
                    std::cout << "Skipped " << n << "s. Song finished." << std::endl;
                }
            }
        }

        // function to remove a song from the playlists (if it exists)
        void remove(std::string nameSong)
        {   
            bool found = false;
            for (int i = 0; i < playlistVip.getSize(); i++){
                Song song = playlistVip.dequeue();
                if (song.name == nameSong)
                {
                    std::cout << "Removed: " << song.name << std::endl;
                    found = true;
                }
                else 
                {
                    playlistVip.enqueue(song);
                }

            }
            if (found) return;
        

            for (int i = 0; i < playlistRegular.getSize(); i++)
            {
                Song song = playlistRegular.dequeue();
                if (song.name == nameSong)
                {
                    std::cout << "Removed: " << song.name << std::endl;
                    found = true;
                }
                else
                {
                    playlistRegular.enqueue(song);
                }
            }
            if (found) return;

            for (int i = 0; i < playlistLow.getSize(); i++)
            {
                Song song = playlistLow.dequeue();
                if (song.name == nameSong)
                {
                    std::cout << "Removed: " << song.name << std::endl;
                    found = true;
                }
                else
                {
                    playlistLow.enqueue(song);
                }
            }

            if (!found) {
                std::cout << "Song not found in any playlist." << std::endl;
            };
        }

        // function to replay the last played song 
        void replay(){
            if (history_of_played_songs.isEmpty())
            {
                std::cout << "There are no songs in the history." << std::endl;
            }
            else
            {
                Song last_played_song = history_of_played_songs.peekLast();
                if (last_played_song.preference == Song::Type::VIP)
                {
                    playlistVip.enqueue(last_played_song);

                    while (last_played_song.name != playlistVip.peek().name)
                    {
                        Song song = playlistVip.dequeue();
                        playlistVip.enqueue(song);
                    }
                }
                else if (last_played_song.preference == Song::Type::Regular)
                {
                    playlistRegular.enqueue(last_played_song);

                    while (last_played_song.name != playlistRegular.peek().name)
                    {
                        Song song = playlistRegular.dequeue();
                        playlistRegular.enqueue(song);
                    }
                }
                else if (last_played_song.preference == Song::Type::Low)
                {
                    playlistLow.enqueue(last_played_song);

                    while (last_played_song.name != playlistLow.peek().name)
                    {
                        Song song = playlistLow.dequeue();
                        playlistLow.enqueue(song);
                    }
                }
                std::cout << "Replaying: " << last_played_song.name << std::endl;
                play(true); // call play with the "replay" flag to avoid duplicating the output
            }
        }
};


int main()
{   
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); // redirect input and output to files
    DJ dj;

    std::string command;
    int preference;
    int time_interval;
    std::string name;
    while (!std::cin.eof()) // read commands to the end of the file
    {
        readCmd(command, preference, time_interval, name);

        if (command == "ADD")
        {
            Song song = Song(static_cast<Song::Type>(preference), time_interval, name);
            dj.add(song);
        }

        else if (command == "PLAY")
        {
            dj.play();
        }

        else if (command == "HISTORY")
        {
            dj.history();
        }

        else if (command == "SHOW")
        {
            dj.show();
        }

        else if (command == "SKIP")
        {
            dj.skip(time_interval);
        }

        else if (command == "REMOVE")
        {
            dj.remove(name);
        }

        else if (command == "REPLAY")
        {
            dj.replay();
        }
    }

    return 0;
}

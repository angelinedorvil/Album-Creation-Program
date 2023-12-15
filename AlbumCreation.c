#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 4

struct track {
   char* name; // Title of the track
   int duration; // Duration of the track, in minutes
}; 
typedef struct track Track;


struct album {
   Track* tracks; 
   int numberOfTracks; // current # of tracks stored in this album
   int maxNumberOfTracks; // maximum # of tracks the album can store
};
typedef struct album Album;


Track* tracks_allocate(int size){
	Track* tracks = (Track*)malloc(size *sizeof(Track));
	
	if (tracks == NULL) {
		//printf("Memory allocation of tracks failed.\n");
		return NULL;
	}

	for (int i = 0; i < size; ++i){
		tracks[i].name = NULL;
		tracks[i].duration = 0;
	}
	
	return tracks;
}

void tracks_deallocate(Track* ptr, int numberOfTracks){
	if (ptr == NULL){
		//printf("Pointer is NULL. Nothing to deallocate.\n");
		return;
	}
	
	for (int i = 0; i < numberOfTracks; ++i){
		if (ptr[i].name){
		free(ptr[i].name);
		ptr[i].name = NULL;
		}
	}
	
	free(ptr);
	//printf("Memory of tracks deallocated successfully.\n");
}

Album* album_allocate(int size){
	Album* new_album = (Album*)malloc(size *sizeof(Album));

	if (new_album == NULL) {
		//printf("Memory allocation of album failed.\n");
		return NULL;
	}

	new_album->maxNumberOfTracks = size;
	new_album->numberOfTracks = 0;
	
	new_album->tracks = tracks_allocate(size);
	
	if (new_album->tracks == NULL) {
		//printf("Memory allocation of album tracks failed.\n");
		free(new_album);
		return NULL;
	}
	
	return new_album;
}


void album_deallocate(Album* ptr){
	if (ptr == NULL){
		//printf("Pointer is NULL. Nothing to deallocate.\n");
		return;
	} else{
		tracks_deallocate(ptr->tracks, ptr->numberOfTracks);
		free(ptr);
		//printf("Memory of album deallocated successfully.\n");
	}
}

void album_add(Album* ptr, char* trackName, int trackDuration){
	if (ptr == NULL){
		//printf("Album pointer is NULL. Cannot add track info.\n");
		return;
	}
	
	for (int i = 0; i < ptr->maxNumberOfTracks; ++i){
		if (ptr->tracks[i].name == NULL){
		ptr->tracks[i].name = strdup(trackName);
		ptr->tracks[i].duration = trackDuration;
		ptr->numberOfTracks++;
		//printf("track '%s' added to the album.\n", trackName);
		return;
		}
	}
	
	if (ptr->numberOfTracks >= ptr-> maxNumberOfTracks) {
		//printf("Cannot add more tracks; Album at max capacity.\n");
		return;
	}
	
}

void album_display(Album* ptr){
	if (ptr == NULL){
		//printf("Album is empty.\n");
		return;
	}
	
	printf("Displaying Album with %d Title(s):\n", ptr->numberOfTracks);
	for (int i = 0; i < ptr->numberOfTracks; ++i){
		if (ptr->tracks[i].duration <= 1){
			printf("#%d\t (%d minute)\t \"%s\"\n", i + 1, ptr->tracks[i].duration, ptr->tracks[i].name);
		} else{
			printf("#%d\t (%d minutes)\t \"%s\"\n", i + 1, ptr->tracks[i].duration, ptr->tracks[i].name);
		}
	}
}

int main (){
   Album* ptr = album_allocate(MAXSIZE); 
   album_add(ptr, "The ballad of Bilbo Baggins", 1);
   album_add(ptr, "Where the Eagles do not fly", 5);
   album_add(ptr, "Another Hobbit bites the dust", 8);
   album_add(ptr, "One Precious to rule them all", 20);
   album_add(ptr, "One does not simply sings about LOTR", 6);
   album_display(ptr);
   album_deallocate(ptr);
   return EXIT_SUCCESS;
}

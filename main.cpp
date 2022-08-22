#include <iostream>
#include <vector>
#include <SDL.h>

using namespace std;

SDL_Event event;
SDL_bool done = SDL_FALSE;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
double screen_w = (double) SCREEN_WIDTH;
double screen_h = (double) SCREEN_HEIGHT;

const int N = 1e3+10;

int n, m;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

bool visited[N][N];
long long cnt = 0;

void generate_maze(int x, int y){
    visited[x][y] = true;
    vector<pair<int, int>> available;
    cnt++;
    cout << cnt << endl;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx > n-1 || ny < 0 || ny > m-1 || visited[nx][ny])
            continue;
        available.emplace_back(nx, ny);
    }

    SDL_Rect cur;
    cur.x = (int)(2 + screen_w / m * y);
    cur.y = (int)(2 + screen_h / n * x);
    cur.w = (int)(screen_w / m - 1);
    cur.h = (int)(screen_h / n - 1);

    while (!available.empty()) {
        int next = rand() % (int)available.size();
        int sx = available[next].first, sy = available[next].second;
        available.erase(available.begin() + next);
        if (visited[sx][sy])
            continue;

        SDL_Rect scur;
        scur.x = (int)(2 + screen_w / m * sy);
        scur.y = (int)(2 + screen_h / n * sx);
        scur.w = (int)(screen_w / m - 1);
        scur.h = (int)(screen_h / n - 1);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &scur);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &cur);

        if (x == sx) {
            SDL_RenderDrawLine(renderer, (int)(1 + screen_w / m * max(y, sy)), (int)(1 + screen_h / n * x),
                               (int)(1 + screen_w / m * max(y, sy)), (int)(1 + screen_h / n * (x + 1)));

        } else if (y == sy) {
            SDL_RenderDrawLine(renderer, (int)(1 + screen_w / m * y), (int)(1 + screen_h / n * max(x, sx)),
                               (int)(1 + screen_w / m * (y + 1)), (int)(1 + screen_h / n * max(x, sx)));
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
                return;
            }
        }

        SDL_Delay(1000/144);
        SDL_RenderPresent(renderer);

        generate_maze(sx, sy);

        if (done)
            return;

        SDL_RenderFillRect(renderer, &scur);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &cur);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_Delay(1000/144);
        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char* args[]) {
    cin >> n >> m;
    bool first = true;

    srand(time(nullptr));

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        if (SDL_CreateWindowAndRenderer((int)SCREEN_WIDTH, (int)SCREEN_HEIGHT, 0, &window, &renderer) == 0) {
            while (!done) {
                if (first) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

                    screen_h -= 4;
                    screen_w -= 4;
                    for (int i = 0; i <= n; ++i) {
                        for (int j = 0; j <= m; ++j) {
                            visited[i][j] = false;
                            if (j != m)
                                SDL_RenderDrawLine(renderer, (int)(1 + screen_w / m * j), (int)(1 + screen_h / n * i),
                                                   (int)(1 + screen_w / m * (j + 1)), (int)(1 + screen_h / n * i));
                            if (i != n)
                                SDL_RenderDrawLine(renderer, (int)(1 + screen_w / m * j), (int)(1 + screen_h / n * i),
                                                   (int)(1 + screen_w / m * j), (int)(1 + screen_h / n * (i + 1)));
                        }
                    }
                    SDL_RenderPresent(renderer);

                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, (int)(1 + screen_w), (int)(1 + screen_h / n * (n - 1)), (int)(1 + screen_w),
                                       (int)(1 + screen_h));

                    generate_maze(0, 0);
                    SDL_RenderPresent(renderer);
                    first = false;
                }

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }

                SDL_Delay(1000/144);
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}

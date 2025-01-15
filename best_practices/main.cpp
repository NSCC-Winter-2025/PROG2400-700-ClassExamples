#include "best_practices_app.h"

int main() {

    BestPracticesApp app;
    app.read_config();
    app.read_saved_results();
    app.run();
    app.save_results();

    return 0;
}

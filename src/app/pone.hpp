/*    Created:    10-17-2025
 *    Modified:   10-17-2025
 */

#pragma once

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class GD_Pone : public Sprite2D {
    GDCLASS(GD_Pone, Sprite2D)

   private:
    double m_timePassed;

   protected:
    static void _bind_methods();

   public:
    GD_Pone();
    ~GD_Pone();

    void _process(double delta) override;
};

}  // namespace godot

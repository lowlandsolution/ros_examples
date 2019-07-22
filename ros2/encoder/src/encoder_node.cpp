#include <chrono>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <encoder_msgs/msg/encoder_feedback.hpp>

using namespace std::chrono_literals;

class EmulatedEncoder : public rclcpp::Node
{
public:
    EmulatedEncoder()
    : Node("emulated_encoder"), m_ticks(0)
    {
        m_publisher = create_publisher<encoder_msgs::msg::EncoderFeedback>("topic", 10);
        auto timer_callback =
            [this]() -> void {
                auto message = encoder_msgs::msg::EncoderFeedback();
                message.ticks = m_ticks++;
                m_publisher->publish(message);
        };
        m_timer = create_wall_timer(500ms, timer_callback);
    }

private:
    rclcpp::TimerBase::SharedPtr m_timer;
    rclcpp::Publisher<encoder_msgs::msg::EncoderFeedback>::SharedPtr m_publisher;
    unsigned int m_ticks;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<EmulatedEncoder>());
    rclcpp::shutdown();
}

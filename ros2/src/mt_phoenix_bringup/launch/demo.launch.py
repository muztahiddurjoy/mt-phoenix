from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Launch the demo node
        Node(
            package='mt_phoenix_demo',
            executable='demo_node',
            name='demo_node',
            output='screen',
            parameters=[{'use_sim_time': False}]
        ),
    ])
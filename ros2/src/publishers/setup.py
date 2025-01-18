from setuptools import find_packages, setup

package_name = 'publishers'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='muztahid',
    maintainer_email='muztahiddurjoy99@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'keyboard_control = publishers.keyboard_control:main',
            'wireless_joy_control = publishers.joysticks.wireless_joystick_control:main',
            'logitech_joy_control = publishers.joysticks.logitech_joystick_control:main',
        ],
    },
)

<?php

// autoload_static.php @generated by Composer

namespace Composer\Autoload;

class ComposerStaticInit5155dd5c4fd4d786cbc59ee828a37196
{
    public static $prefixLengthsPsr4 = array (
        'S' => 
        array (
            'Symfony\\Component\\Process\\' => 26,
        ),
    );

    public static $prefixDirsPsr4 = array (
        'Symfony\\Component\\Process\\' => 
        array (
            0 => __DIR__ . '/..' . '/symfony/process',
        ),
    );

    public static $prefixesPsr0 = array (
        'R' => 
        array (
            'RobbieP\\ZbarQrdecoder\\' => 
            array (
                0 => __DIR__ . '/..' . '/robbiep/zbar-qrdecoder/src',
            ),
        ),
    );

    public static function getInitializer(ClassLoader $loader)
    {
        return \Closure::bind(function () use ($loader) {
            $loader->prefixLengthsPsr4 = ComposerStaticInit5155dd5c4fd4d786cbc59ee828a37196::$prefixLengthsPsr4;
            $loader->prefixDirsPsr4 = ComposerStaticInit5155dd5c4fd4d786cbc59ee828a37196::$prefixDirsPsr4;
            $loader->prefixesPsr0 = ComposerStaticInit5155dd5c4fd4d786cbc59ee828a37196::$prefixesPsr0;

        }, null, ClassLoader::class);
    }
}

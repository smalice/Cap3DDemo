using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace CapgeminiXNA
{
    public class Game : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Models models;

        public Camera camera { get; protected set; }

        private Vector3 sCamPos = new Vector3(0, -5, 100);
        private Vector3 sCamTar = new Vector3(0, -5, 0);
        private Vector3 sCamUp = Vector3.Up;
        private const int resWidth = 1280;
        private const int resHeight = 1024;

        public Game()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";

            graphics.PreferredBackBufferWidth = resWidth;
            graphics.PreferredBackBufferHeight = resHeight;
            //#if !DEBUG     
            graphics.IsFullScreen = true;
            //#endif
        }
        
        protected override void Initialize()
        {
            camera = new Camera(this, sCamPos, sCamTar, sCamUp);
            Components.Add(camera);

            models = new Models(this);
            Components.Add(models);

            base.Initialize();
        }

        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);
        }

        protected override void UnloadContent() { }

        protected override void Update(GameTime gameTime)
        {
            GamePadMovement();

            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Azure);

            base.Draw(gameTime);
        }

        private void GamePadMovement()
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
            { this.Exit(); }
            if (GamePad.GetState(PlayerIndex.One).Buttons.Start == ButtonState.Pressed)
            { }
        }

    }

}

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
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

namespace CapgeminiXNA
{

    public class Camera : Microsoft.Xna.Framework.GameComponent
    {

        public Matrix view { get; protected set; }
        public Matrix projection { get; protected set; }

        public Vector3 cameraPosition { get; protected set; }

        public Vector3 cameraDirection;
        public Vector3 cameraUp;

        private float speed = 3;
        private float thumbStickMod = 6;

        public Camera(Game game, Vector3 pos, Vector3 target, Vector3 up) : base(game)
        {

            cameraPosition = pos;
            cameraDirection = target - pos;
            cameraDirection.Normalize();
            cameraUp = up;
            
            CreateLookAt();

            projection = Matrix.CreatePerspectiveFieldOfView
                ( MathHelper.PiOver4, (float)Game.Window.ClientBounds.Width / (float)Game.Window.ClientBounds.Height,  1, 3000);
        }

        public override void Initialize()
        {
            base.Initialize();
        }

        public override void Update(GameTime gameTime)
        {
            GamePadMovement();

            CreateLookAt();

            base.Update(gameTime);
        }

        private void GamePadMovement()
        {
            GamePadState state = GamePad.GetState(PlayerIndex.One);

            cameraPosition += cameraDirection * speed * state.ThumbSticks.Left.Y;
            cameraPosition -= Vector3.Cross(cameraUp, cameraDirection) * speed * state.ThumbSticks.Left.X;

            cameraDirection = Vector3.Transform(cameraDirection,
                Matrix.CreateFromAxisAngle(cameraUp, (-MathHelper.PiOver4 / 150) * (state.ThumbSticks.Right.X * thumbStickMod)));

            cameraDirection = Vector3.Transform(cameraDirection,
                Matrix.CreateFromAxisAngle(Vector3.Cross(cameraUp, cameraDirection),(MathHelper.PiOver4 / 100) * (state.ThumbSticks.Right.Y * -thumbStickMod)));

            //cameraUp = Vector3.Transform(cameraUp,
            //    Matrix.CreateFromAxisAngle(Vector3.Cross(cameraUp, cameraDirection),
            //    (MathHelper.PiOver4 / 100) *
            //    (state.ThumbSticks.Right.Y * -thumbStickMod)));
        }

        private void CreateLookAt()
        {
            view = Matrix.CreateLookAt(cameraPosition,
                cameraPosition + cameraDirection, cameraUp);
        }
    }
}

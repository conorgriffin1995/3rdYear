﻿using System.Data.Entity;
using MvcApplication3.Models;

namespace MvcApplication3.MovieDBContext__MvcMovie
{
    public class Models_ : DbContext
    {
        // You can add custom code to this file. Changes will not be overwritten.
        // 
        // If you want Entity Framework to drop and regenerate your database
        // automatically whenever you change your model schema, add the following
        // code to the Application_Start method in your Global.asax file.
        // Note: this will destroy and re-create your database with every model change.
        // 
        // System.Data.Entity.Database.SetInitializer(new System.Data.Entity.DropCreateDatabaseIfModelChanges<MvcApplication3.MovieDBContext__MvcMovie.Models_>());

        public Models_() : base("name=Models_")
        {
        }

        public DbSet<Movie> Movies { get; set; }
    }
}
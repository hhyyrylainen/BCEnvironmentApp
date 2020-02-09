BCEnvironmentApp
================

This is a behaviour changing app for environmentally good
behaviours. This is implemented as a web app using ruby on rails.

This project was done for the persuasive design course at the
University of Oulu.

See LICENSE for licensing terms of this code.

Running
-------

Pretty standard rails workflow.

After cloning run (NOTE: you might want to setup rbenv first to get
the right ruby version):

```sh
bundle install --deployment --path vendor/bundle
bundle exec rails secret # replace KEY with the output from this
SECRET_KEY_BASE=KEY RAILS_ENV=production bundle exec rails db:create db:migrate assets:clobber assets:precompile
```

And then run rails and sidekiq with the correct environment variables
set. For example with systemd service files.


After setting up you need to run this rake task once:

```sh
bundle exec rake bce:check_tasks
```

to start the background jobs that remind users and refresh the daily
tasks.


After registering you can make your account an admin with this:
```sh
bundle exec rake bce:grant_admin[your@email.here]
```
